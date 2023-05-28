#ifndef __SHARE_H__
#define __SAHRE_H__

#include "../memory_map.h"
#include "xil_printf.h"
#include "../ftl_config.h"
#include "../data_buffer.h"
#include "../address_translation.h"
#include <inttypes.h>
#include <assert.h>

void handle_nvme_io_share_v2(unsigned int cmdSlotTag, NVME_IO_COMMAND *nvmeIOCmd, unsigned int qID);
void DiscardBlocks(unsigned int start_lba, unsigned int len);
#endif
