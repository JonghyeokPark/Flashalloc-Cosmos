
#ifndef STREAM_H_
#define STREAM_H_

#include "../nvme/nvme_io_cmd.h"
#include "../nvme/nvme.h"
#include "../memory_map.h"
#include "../nvme_io_cmd_completion.h"


#define TOTAL_STREAMS		8
#define NOSTREAM			-1

// TODO(optimization): get XXX value and extract dieNo and blockNo

// how to get current block of die ?
// - virtualDieMapPtr->die[dieNo].currentBlock;

 typedef struct stream_oblect {
	unsigned int dieNo;
	unsigned int blockNo;
	unsigned int pageCnt;
} SO;

extern SO stream_controller[TOTAL_STREAMS];

void stream_init();
void stream_insert_or_update(unsigned int stream_id, unsigned int dieNo, unsigned blockNo);
unsigned int stream_to_vsa(unsigned int stream_id);
void stream_write(unsigned int cmdSlotTag, NVME_IO_COMMAND *nvmeIOCmd, unsigned int qID);
void stream_set(unsigned int cmdSlotTag, NVME_IO_COMMAND *nvmeIOCmd, unsigned int qID);

#endif
