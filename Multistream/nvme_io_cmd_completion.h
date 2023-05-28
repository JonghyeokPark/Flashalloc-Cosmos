/*
 * nvme_io_cmd_completion.h
 *
 *  Created on: 2021. 7. 14.
 *      Author: SIY
 */

#ifndef SRC_NVME_IO_CMD_COMPLETION_H_
#define SRC_NVME_IO_CMD_COMPLETION_H_
#pragma once

#include "xil_printf.h"
#include "nvme/host_lld.h"

#define PRINT_DEBUG_MSG_FUA				0
#define TEST_MODE_FUA					0 //0:test OFF 1:force ON 2:force OFF

typedef enum _NAND_OPERATION_RESULT
{
	NAND_RESULT_UNDEFINED,
	NAND_RESULT_DONE,
	NAND_RESULT_READ_DONE_UNCORRECTABLE_SOON,
	NAND_RESULT_READ_FAIL_TRIGGER,
	NAND_RESULT_READ_FAIL_TRANSFER,
	NAND_RESULT_PROGRAM_FAIL,
	NAND_RESULT_ERASE_FAIL
} NAND_OPERATION_RESULT;


typedef struct _NVME_IO_CMD_COMPLETE_ENTRY
{
	unsigned int qID						:16;
	unsigned int cID						:16;
	unsigned int notIssuedRxCount			:16;
	unsigned int notCompletedRxCount		:16;
	unsigned int notIssuedTxCount			:16;
	unsigned int notCompletedTxCount		:16;
	unsigned int notCompletedNANDReadCount	:16;
	unsigned int notCompletedNANDWriteCount	:16;
	unsigned int fua						:1;
	unsigned int fail						:1;
	unsigned int reserved0					:31;
} NVME_IO_CMD_COMPLETE_ENTRY, *P_NVME_IO_CMD_COMPLETE_ENTRY;

typedef struct _NVME_IO_CMD_COMPLETE_TABLE
{
	NVME_IO_CMD_COMPLETE_ENTRY nvmeIoCmdCompleteEntry[MAX_CMD_SLOT_TAG];
} NVME_IO_CMD_COMPLETE_TABLE, *P_NVME_IO_CMD_COMPLETE_TABLE;


void InitNvmeIoCmdCompleteTable();
void SetFUANvmeIoCmd(unsigned int cmdSlotTag, unsigned int reqSlotTag, unsigned int qID, unsigned int cID);
unsigned int GetFUANvmeIoCmd(unsigned int cmdSlotTag);
unsigned int GetQIDNvmeIoCmd(unsigned int cmdSlotTag);
unsigned int GetCIDNvmeIoCmd(unsigned int cmdSlotTag);
void ResetFUANvmeIoCmd(unsigned int cmdSlotTag, unsigned int reqSlotTag);
void AllocateNotIssuedRxforNvmeIoCmd(unsigned int cmdSlotTag, unsigned int buffEnty, unsigned int devAddr);
void AllocateNotIssuedTxforNvmeIoCmd(unsigned int cmdSlotTag, unsigned int buffEnty, unsigned int devAddr);
void AllocateNotCompletedRxforNvmeIoCmd(unsigned int cmdSlotTag, unsigned int buffEnty, unsigned int devAddr);
void AllocateNotCompletedTxforNvmeIoCmd(unsigned int cmdSlotTag, unsigned int buffEnty, unsigned int devAddr);
void AllocateNotCompletedNandReadforNvmeIoCmd(unsigned int cmdSlotTag, unsigned int reqSlotTag, unsigned int buffEnty, unsigned int devAddr);
void AllocateNotCompletedNandWriteforNvmeIoCmd(unsigned int cmdSlotTag, unsigned int reqSlotTag, unsigned int buffEnty, unsigned int devAddr);
void IssuedRxforNvmeIoCmd(unsigned int cmdSlotTag, unsigned int reqSlotTag, unsigned int reqCode);
void IssuedTxforNvmeIoCmd(unsigned int cmdSlotTag, unsigned int reqSlotTag, unsigned int reqCode);
void CompleteRxforNvmeIoCmd(unsigned int cmdSlotTag, unsigned int reqSlotTag, unsigned int reqCode);
void CompleteTxforNvmeIoCmd(unsigned int cmdSlotTag, unsigned int reqSlotTag, unsigned int reqCode);
void CompleteNandReqforNvmeIoCmd(unsigned int cmdSlotTag, unsigned int reqSlotTag, unsigned int reqCode, unsigned int reqStatus);

extern P_NVME_IO_CMD_COMPLETE_TABLE nvmeIoCmdCompletionTablePtr;

#endif /* SRC_NVME_IO_CMD_COMPLETION_H_ */
