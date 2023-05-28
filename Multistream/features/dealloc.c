#include "../memory_map.h"
#include "xil_printf.h"
#include "../ftl_config.h"
#include "../data_buffer.h"
#include <inttypes.h>
#include <assert.h>
#include <features/dealloc.h>


// (jhpark): deallocate
///////////////////////////////////////////////////////////////////////////////////////////////////
void InvalidVirtualSlice(unsigned int logicalSliceAddr)
{
   unsigned int dieNo, blockNo, virtualSliceAddr, pageNo, reqSlotTag;

   virtualSliceAddr = logicalSliceMapPtr->logicalSlice[logicalSliceAddr].virtualSliceAddr;

   if(virtualSliceAddr == VSA_NONE) {
      return;
   }

#ifdef TRIMD_DEBUG
   if (CheckDataBufHitForTRIM(logicalSliceAddr) != DATA_BUF_FAIL) {
	   xil_printf("[DEBUG] (to be) TRIM lsa is still in the buffer lsa:%u\n", logicalSliceAddr);
   }
#endif

   SyncBlockedNandReqDone();
   InvalidateOldVsa(logicalSliceAddr);
   SyncBlockedNandReqDone();

   dieNo = Vsa2VdieTranslation(virtualSliceAddr);
   blockNo = Vsa2VblockTranslation(virtualSliceAddr);
   pageNo = Vsa2VpageTranslation(virtualSliceAddr);

   // jhpark? why?
   /*
   if(pageNo == virtualBlockMapPtr->block[dieNo][blockNo].currentPage
		   && virtualBlockMapPtr->block[dieNo][blockNo].currentPage < USER_PAGES_PER_BLOCK)
      virtualBlockMapPtr->block[dieNo][blockNo].currentPage++;
   */

   // (jhpark): is this needed?
   //virtualSliceMapPtr->virtualSlice[virtualSliceAddr].logicalSliceAddr = VSA_NONE;
   g_ftl_num_trim++;

}

void deallocate(unsigned int startLba, unsigned int lengthOfLba)
{
      unsigned int requestedNvmeBlock, transCounter, tempLsa, loop;

      requestedNvmeBlock = lengthOfLba + 1;
      transCounter = 0;
      tempLsa = startLba / NVME_BLOCKS_PER_SLICE;
      loop = ((startLba % NVME_BLOCKS_PER_SLICE) + requestedNvmeBlock) / NVME_BLOCKS_PER_SLICE;
      InvalidVirtualSlice(tempLsa);

      tempLsa++;
      transCounter++;

      while(transCounter < loop)
      {
         InvalidVirtualSlice(tempLsa);

         tempLsa++;
         transCounter++;
      }

      if(loop == 0)
         return ;

      InvalidVirtualSlice(tempLsa);
}
/////////////////////////////////////////////////////////////////////////////////////////////
