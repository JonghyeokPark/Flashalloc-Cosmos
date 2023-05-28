#include <features/stream.h>

SO stream_controller[TOTAL_STREAMS];

void stream_set(unsigned int cmdSlotTag, NVME_IO_COMMAND *nvmeIOCmd, unsigned int qID) {
	unsigned int requestedNvmeBlock, tempNumOfNvmeBlock, transCounter, tempLsa, loop;


	IO_READ_COMMAND_DW12 writeInfo12;
	writeInfo12.dword = nvmeIOCmd->dword[12];
	unsigned int len =  writeInfo12.NLB;
	unsigned int offset = nvmeIOCmd->dword[10];

	IO_READ_COMMAND_DW15 writeInfo15;
	writeInfo15.dword = nvmeIOCmd->dword[15];
	unsigned int stream_id = writeInfo15.dword;


	requestedNvmeBlock = len+1;
	transCounter = 0;
	tempLsa = offset / NVME_BLOCKS_PER_SLICE;

	loop = ((offset % NVME_BLOCKS_PER_SLICE) + requestedNvmeBlock) / NVME_BLOCKS_PER_SLICE;
	logicalSliceMapPtr->logicalSlice[tempLsa].stream_id = stream_id;

	tempLsa++;
	transCounter++;

	while(transCounter < loop) {
		logicalSliceMapPtr->logicalSlice[tempLsa].stream_id = stream_id;
		tempLsa++;
		transCounter++;
	}

	tempNumOfNvmeBlock = (offset + requestedNvmeBlock) % NVME_BLOCKS_PER_SLICE;
	if((tempNumOfNvmeBlock == 0) || (loop == 0))
		return ;

	logicalSliceMapPtr->logicalSlice[tempLsa].stream_id = stream_id;
}

void stream_write(unsigned int cmdSlotTag, NVME_IO_COMMAND *nvmeIOCmd, unsigned int qID) {

	IO_READ_COMMAND_DW12 writeInfo12;

	//IO_READ_COMMAND_DW13 writeInfo13;
	IO_READ_COMMAND_DW15 writeInfo15;
	unsigned int startLba[2];
	unsigned int nlb, fua, cID, stream_id;

	writeInfo12.dword = nvmeIOCmd->dword[12];
	writeInfo15.dword = nvmeIOCmd->dword[15];

	startLba[0] = nvmeIOCmd->dword[10];
	startLba[1] = nvmeIOCmd->dword[11];
	nlb = writeInfo12.NLB;
	fua = writeInfo12.FUA;
	cID = nvmeIOCmd->CID;
	stream_id = writeInfo15.dword;

	//printf("multi-stream write lba: %d len: %d stream-id: %d\n", startLba[0], nlb, stream_id);

	ASSERT(startLba[0] < storageCapacity_L && (startLba[1] < STORAGE_CAPACITY_H || startLba[1] == 0));
	ASSERT(nlb < MAX_NUM_OF_NLB);
	ASSERT((nvmeIOCmd->PRP1[0] & 0xF) == 0 && (nvmeIOCmd->PRP2[0] & 0xF) == 0);
	ASSERT(nvmeIOCmd->PRP1[1] < 0x10000 && nvmeIOCmd->PRP2[1] < 0x10000);

	ReqTransNvmeToSlice(cmdSlotTag, qID, cID, startLba[0], nlb, IO_NVM_WRITE, fua, stream_id);
}

void stream_init(){
	for (int i=0; i<TOTAL_STREAMS; ++i){
		stream_controller[i].dieNo = -1;
		stream_controller[i].blockNo = -1;
	}
}

// update current block id for given stream_id
// insert if there is no streamed block
void stream_insert_or_update(unsigned int stream_id, unsigned int dieNo, unsigned blockNo) {
	stream_controller[stream_id].dieNo = dieNo;
	stream_controller[stream_id].blockNo = blockNo;
}

// return vsa (where pageNo == 0) for given stream_id
unsigned int stream_to_vsa(unsigned int stream_id) {
	return Vorg2VsaTranslation(stream_controller[stream_id].dieNo, stream_controller[stream_id].blockNo, 0);
}
