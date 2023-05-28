#include "share.h"

#include "../ftl_stats.h"
extern struct stats_ftl stats_ftl;
static void InvalidateDataBuffer(unsigned int bufEntry)
{
    unsigned int prevEntry, nextEntry, tailEntry;

    if (dataBufLruList.tailEntry == bufEntry)
        goto invalidate;

    /* del bufEntry from LRU list */
    prevEntry = dataBufMapPtr->dataBuf[bufEntry].prevEntry;
    nextEntry = dataBufMapPtr->dataBuf[bufEntry].nextEntry;

    if (nextEntry != DATA_BUF_NONE && prevEntry != DATA_BUF_NONE) {
        dataBufMapPtr->dataBuf[prevEntry].nextEntry = nextEntry;
        dataBufMapPtr->dataBuf[nextEntry].prevEntry = prevEntry;
    } else if (nextEntry == DATA_BUF_NONE && prevEntry != DATA_BUF_NONE) {
        assert(0); // bufentry should be already in tail
    } else if (nextEntry != DATA_BUF_NONE && prevEntry == DATA_BUF_NONE) {
        dataBufLruList.headEntry = nextEntry;
        dataBufMapPtr->dataBuf[nextEntry].prevEntry = DATA_BUF_NONE;
    } else {
        assert(0);
    }

invalidate:
    /* insert bufEntry to tail */
    tailEntry = dataBufLruList.tailEntry;
    assert(tailEntry != DATA_BUF_NONE);

    dataBufLruList.tailEntry = bufEntry;
    dataBufMapPtr->dataBuf[tailEntry].nextEntry = bufEntry;

    dataBufMapPtr->dataBuf[bufEntry].prevEntry = tailEntry;
    dataBufMapPtr->dataBuf[bufEntry].nextEntry = DATA_BUF_NONE;

    /* remove from hash list */
    SelectiveGetFromDataBufHashList(bufEntry);

    dataBufMapPtr->dataBuf[bufEntry].logicalSliceAddr = LSA_NONE;
    dataBufMapPtr->dataBuf[bufEntry].dirty = DATA_BUF_CLEAN;
}

static void share_core(unsigned int lsa1, unsigned int lsa2, unsigned int cmdSlotTag,
                NVME_IO_COMMAND *nvmeIOCmd, unsigned int qID)
{
	unsigned int lsa1_bufEntry = CheckDataBufHitForShare(lsa1);
	unsigned int lsa2_bufEntry = CheckDataBufHitForShare(lsa2);
    unsigned int vsa1;

    if (lsa1_bufEntry == DATA_BUF_FAIL && lsa2_bufEntry == DATA_BUF_FAIL) {
        vsa1 = logicalSliceMapPtr->logicalSlice[lsa1].virtualSliceAddr;
        InvalidateOldVsa(lsa2);

        logicalSliceMapPtr->logicalSlice[lsa2].virtualSliceAddr = vsa1;
        virtualSliceMapPtr->virtualSlice[vsa1].logicalSliceAddr = lsa2;

        logicalSliceMapPtr->logicalSlice[lsa1].virtualSliceAddr = VSA_NONE;

    } else if (lsa1_bufEntry != DATA_BUF_FAIL && lsa2_bufEntry == DATA_BUF_FAIL) {
        InvalidateOldVsa(lsa2);

        /* delete from current lsa2 hash buf list */
        SelectiveGetFromDataBufHashList(lsa1_bufEntry);

        dataBufMapPtr->dataBuf[lsa1_bufEntry].logicalSliceAddr = lsa2;
        dataBufMapPtr->dataBuf[lsa1_bufEntry].dirty = DATA_BUF_DIRTY;

        logicalSliceMapPtr->logicalSlice[lsa1].virtualSliceAddr = VSA_NONE;

        /* insert new lsa1 hash buf list */
        PutToDataBufHashList(lsa1_bufEntry);
    } else if (lsa1_bufEntry == DATA_BUF_FAIL && lsa2_bufEntry != DATA_BUF_FAIL) {
        vsa1 = logicalSliceMapPtr->logicalSlice[lsa1].virtualSliceAddr;

        assert(dataBufMapPtr->dataBuf[lsa2_bufEntry].logicalSliceAddr == lsa2);
        InvalidateDataBuffer(lsa2_bufEntry);
        InvalidateOldVsa(lsa2);

        logicalSliceMapPtr->logicalSlice[lsa2].virtualSliceAddr = vsa1;
        virtualSliceMapPtr->virtualSlice[vsa1].logicalSliceAddr = lsa2;

        logicalSliceMapPtr->logicalSlice[lsa1].virtualSliceAddr = VSA_NONE;
    } else {
        /*
         * if lsa1, lsa2 is not NONE, lsa1-buf invalidated and
         * lsa1 take lsa2-buf-entry
         */
        assert(dataBufMapPtr->dataBuf[lsa2_bufEntry].logicalSliceAddr == lsa2);
        InvalidateDataBuffer(lsa2_bufEntry);
        InvalidateOldVsa(lsa2);

        /* delete from current lsa1 hash buf list */
        SelectiveGetFromDataBufHashList(lsa1_bufEntry);

        dataBufMapPtr->dataBuf[lsa1_bufEntry].logicalSliceAddr = lsa2;
        dataBufMapPtr->dataBuf[lsa1_bufEntry].dirty = DATA_BUF_DIRTY;

        /* insert new lsa1 hash buf list */
        PutToDataBufHashList(lsa1_bufEntry);
    }
    stats_ftl.share_page_cnt++;
}

void handle_nvme_io_share_v2(unsigned int cmdSlotTag, NVME_IO_COMMAND *nvmeIOCmd, unsigned int qID)
{
	IO_DATASET_MANAGEMENT_COMMAND_DW10 dsm10;
	IO_DATASET_MANAGEMENT_COMMAND_DW11 dsm11;

	dsm10.dword = nvmeIOCmd->dword[10];
	dsm11.dword = nvmeIOCmd->dword[11];

	unsigned int nr, len;

	nr = dsm10.NR;
	len = dsm11.dword;

	unsigned int new_addr = 0;
	unsigned int diff = 	 RESERVED0_START_ADDR  % 4096;
	if (diff != 0) {
		new_addr = 	 RESERVED0_START_ADDR  + (4096 - diff);
	} else {
		new_addr = 	 RESERVED0_START_ADDR ;
	}

	set_direct_rx_dma((new_addr), nvmeIOCmd->PRP1[1], nvmeIOCmd->PRP1[0], 4096);
	check_direct_rx_dma_done();

	unsigned int i, j;
	unsigned int LBA1[2];
	unsigned int LBA2[2];
	unsigned int lba1, lba2;

	for (i=0; i<= nr; i++) {
		DATASET_MANAGEMENT_RANGE_SHARE* dmrs = (DATASET_MANAGEMENT_RANGE_SHARE*)
				(new_addr + (sizeof(*dmrs)*i));

		// (debug)
		len = dmrs->length;
		LBA1[0] = dmrs->LBA1[0];
		LBA2[0] = dmrs->LBA2[0];

		for (j = 0; j <= len; j++) {
			lba1 = LBA1[0] + j;
			lba2 = LBA2[0] + j;

			share_core(lba1, lba2, cmdSlotTag, nvmeIOCmd, qID);
		}
	}
}

void DiscardBlocks(unsigned int start_lba, unsigned int len)
{
    unsigned int lba, buf_entry;

    assert(start_lba == (start_lba / NVME_BLOCKS_PER_SLICE));

    for (lba = start_lba; lba < (start_lba + len); lba++) {
        buf_entry = CheckDataBufHitForShare(lba);

        if (buf_entry != DATA_BUF_FAIL)
            InvalidateDataBuffer(buf_entry);

        stats_ftl.discard_page_cnt++;
        InvalidateOldVsa(lba);
    }
}
