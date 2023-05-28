/*
 * nvme_io_cmd_completion.c
 *
 *  Created on: 2021. 7. 14.
 *      Author: SIY
 */

#include "memory_map.h"
#include "nvme_io_cmd_completion.h"

P_NVME_IO_CMD_COMPLETE_TABLE nvmeIoCmdCompletionTablePtr;

void InitNvmeIoCmdCompleteTable()
{
	nvmeIoCmdCompletionTablePtr = (P_NVME_IO_CMD_COMPLETE_TABLE) NVME_IO_CMD_COMPLETE_TABLE_ADDR;

	for(unsigned int cmdSlotTag=0; cmdSlotTag < MAX_CMD_SLOT_TAG; cmdSlotTag++)
	{
		nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].cID = 0;
		nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].qID = 0;
		nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].notIssuedRxCount = 0;
		nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].notCompletedRxCount = 0;
		nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].notIssuedTxCount =0;
		nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].notCompletedTxCount = 0;
		nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].notCompletedNANDReadCount = 0;
		nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].notCompletedNANDWriteCount = 0;
		nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].fua = REQ_OPT_FORCE_UNIT_ACCESS_OFF;
		nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].fail = 0;
	}
}
void SetFUANvmeIoCmd(unsigned int cmdSlotTag, unsigned int reqSlotTag, unsigned int qID, unsigned int cID)
{
	nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].cID = cID;
	nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].qID = qID;
	nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].fua = REQ_OPT_FORCE_UNIT_ACCESS_ON;
#if (PRINT_DEBUG_MSG_FUA == 1)
	xil_printf("Allocate Nvme Io FUA cmdSlotTag %d reqSlotTag %d qID %d cID %d\r\n", cmdSlotTag, reqSlotTag, qID, cID);
#endif
}
unsigned int GetFUANvmeIoCmd(unsigned int cmdSlotTag)
{
	return nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].fua;
}
unsigned int GetQIDNvmeIoCmd(unsigned int cmdSlotTag)
{
	return nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].qID;
}
unsigned int GetCIDNvmeIoCmd(unsigned int cmdSlotTag)
{
	return nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].cID;
}
void ResetFUANvmeIoCmd(unsigned int cmdSlotTag, unsigned int reqSlotTag)
{
	nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].cID = 0;
	nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].qID = 0;
	nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].notIssuedRxCount = 0;
	nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].notCompletedRxCount = 0;
	nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].notIssuedTxCount =0;
	nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].notCompletedTxCount = 0;
	nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].notCompletedNANDReadCount = 0;
	nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].notCompletedNANDWriteCount = 0;
	nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].fua = 0;
	nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].fail = 0;
}
void AllocateNotIssuedRxforNvmeIoCmd(unsigned int cmdSlotTag, unsigned int buffEnty, unsigned int devAddr)
{
	nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].notIssuedRxCount++;
#if (PRINT_DEBUG_MSG_FUA == 1)
	xil_printf("Allo Rx Nvme Io (Issue) CmdSlotTag %d Cnt %d buffEnty %d devAddr %08x\r\n", cmdSlotTag,
			nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].notIssuedRxCount, buffEnty, devAddr);
#endif
}
void AllocateNotIssuedTxforNvmeIoCmd(unsigned int cmdSlotTag, unsigned int buffEnty, unsigned int devAddr)
{
	nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].notIssuedTxCount++;
#if (PRINT_DEBUG_MSG_FUA == 1)
	xil_printf("Allo Tx Nvme Io (Issue) CmdSlotTag %d Cnt %d buffEnty %d devAddr %08x\r\n", cmdSlotTag,
			nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].notIssuedTxCount, buffEnty, devAddr);
#endif
}
void AllocateNotCompletedRxforNvmeIoCmd(unsigned int cmdSlotTag, unsigned int buffEnty, unsigned int devAddr)
{
	nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].notCompletedRxCount++;
#if (PRINT_DEBUG_MSG_FUA == 1)
	xil_printf("Allo Rx Nvme Io (Complete) CmdSlotTag %d Cnt %d buffEnty %d devAddr %08x\r\n", cmdSlotTag,
			nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].notCompletedRxCount, buffEnty, devAddr);
#endif
}
void AllocateNotCompletedTxforNvmeIoCmd(unsigned int cmdSlotTag, unsigned int buffEnty, unsigned int devAddr)
{
	nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].notCompletedTxCount++;
#if (PRINT_DEBUG_MSG_FUA == 1)
	xil_printf("Allo Tx Nvme Io (Complete) CmdSlotTag %d Cnt %d buffEnty %d devAddr %08x\r\n", cmdSlotTag,
			nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].notCompletedTxCount, buffEnty, devAddr);
#endif
}
void AllocateNotCompletedNandReadforNvmeIoCmd(unsigned int cmdSlotTag, unsigned int reqSlotTag, unsigned int buffEnty, unsigned int devAddr)
{
	nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].notCompletedNANDReadCount++;
#if (PRINT_DEBUG_MSG_FUA == 1)
	xil_printf("Allo Nand Read Nvme Io CmdSlotTag %d reqSlotTag %d Cnt %d buffEnty %d devAddr %08x\r\n", cmdSlotTag, reqSlotTag,
			nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].notCompletedNANDReadCount, buffEnty, devAddr);
#endif
}
void AllocateNotCompletedNandWriteforNvmeIoCmd(unsigned int cmdSlotTag, unsigned int reqSlotTag, unsigned int buffEnty, unsigned int devAddr)
{
	nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].notCompletedNANDWriteCount++;
#if (PRINT_DEBUG_MSG_FUA == 1)
	xil_printf("Allo Nand Write Nvme Io CmdSlotTag %d reqSlotTag %d Cnt %d buffEnty %d devAddr %08x\r\n", cmdSlotTag, reqSlotTag,
			nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].notCompletedNANDWriteCount, buffEnty, devAddr);
#endif
}
void IssuedRxforNvmeIoCmd(unsigned int cmdSlotTag, unsigned int reqSlotTag, unsigned int reqCode)
{
	nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].notIssuedRxCount--;
	reqPoolPtr->reqPool[reqSlotTag].nvmeDmaInfo.issuedFlag = REQ_INFO_ISSUED_FLAG_ON;
	if(nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].notIssuedRxCount == 0)
	{
#if (PRINT_DEBUG_MSG_FUA == 1)
			xil_printf("Issued Rx FUA CmdSlotTag %d reqSlotTag %d reqCode %d dataBuffEntry %d\r\n",
					cmdSlotTag, reqSlotTag, reqCode, reqPoolPtr->reqPool[reqSlotTag].dataBufInfo.entry);
#endif
	}
}
void IssuedTxforNvmeIoCmd(unsigned int cmdSlotTag, unsigned int reqSlotTag, unsigned int reqCode)
{
	nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].notIssuedTxCount--;
	reqPoolPtr->reqPool[reqSlotTag].nvmeDmaInfo.issuedFlag = REQ_INFO_ISSUED_FLAG_ON;
	if(nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].notIssuedTxCount == 0)
	{
#if (PRINT_DEBUG_MSG_FUA == 1)
			xil_printf("Issued Tx FUA CmdSlotTag %d reqSlotTag %d reqCode %d dataBuffEntry %d\r\n",
					cmdSlotTag, reqSlotTag, reqCode, reqPoolPtr->reqPool[reqSlotTag].dataBufInfo.entry);
#endif
	}
}
void CompleteRxforNvmeIoCmd(unsigned int cmdSlotTag, unsigned int reqSlotTag, unsigned int reqCode)
{
	NVME_COMPLETION nvmeCPL;
	nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].notCompletedRxCount--;
#if (PRINT_DEBUG_MSG_FUA == 1)
	xil_printf("Decrease Rx FUA CmdSlotTag %d reqSlotTag %d reqCode %d dataBuffEntry %d Cnt %d\r\n",
			cmdSlotTag, reqSlotTag, reqCode, reqPoolPtr->reqPool[reqSlotTag].dataBufInfo.entry,
			nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].notCompletedRxCount);
#endif

}
void CompleteTxforNvmeIoCmd(unsigned int cmdSlotTag, unsigned int reqSlotTag, unsigned int reqCode)
{
	NVME_COMPLETION nvmeCPL;
	nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].notCompletedTxCount--;
#if (PRINT_DEBUG_MSG_FUA == 1)
		xil_printf("Decrease Tx FUA CmdSlotTag %d reqSlotTag %d reqCode %d dataBuffEntry %d Cnt %d\r\n",
				cmdSlotTag, reqSlotTag, reqCode, reqPoolPtr->reqPool[reqSlotTag].dataBufInfo.entry,
				nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].notCompletedTxCount);
#endif
	if((nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].notCompletedTxCount == 0)
			&&(nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].notCompletedNANDReadCount == 0))
	{
		nvmeCPL.dword[0] = 0;
		nvmeCPL.specific = 0x0;
		nvmeCPL.statusFieldWord = 0;
		nvmeCPL.statusField.DNR = 1;
		if(nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].fail)
		{
			nvmeCPL.statusField.SCT = SCT_MEDIA_AND_DATA_INTEGRITY_ERRORS;
			nvmeCPL.statusField.SC = SC_UNRECOVERED_READ_ERROR;
		}
		else
		{
			nvmeCPL.statusField.SCT = SCT_GENERIC_COMMAND_STATUS;
			nvmeCPL.statusField.SC = SC_SUCCESSFUL_COMPLETION;
		}
		set_nvme_cpl(GetQIDNvmeIoCmd(cmdSlotTag), GetCIDNvmeIoCmd(cmdSlotTag), nvmeCPL.specific, nvmeCPL.statusFieldWord);
		set_nvme_slot_release(cmdSlotTag);
		ResetFUANvmeIoCmd(cmdSlotTag, reqSlotTag);
#if (PRINT_DEBUG_MSG_FUA == 1)
		xil_printf("Complete Tx FUA CmdSlotTag %d reqSlotTag %d reqCode %d dataBuffEntry %d\r\n",
				cmdSlotTag, reqSlotTag, reqCode, reqPoolPtr->reqPool[reqSlotTag].dataBufInfo.entry);
#endif
	}
	else
	{
#if (PRINT_DEBUG_MSG_FUA == 1)
		xil_printf("Hold Tx (for NAND Read) FUA CmdSlotTag %d reqSlotTag %d reqCode %d dataBuffEntry %d\r\n",
				cmdSlotTag, reqSlotTag, reqCode, reqPoolPtr->reqPool[reqSlotTag].dataBufInfo.entry);
#endif
	}
}
void CompleteNandReqforNvmeIoCmd(unsigned int cmdSlotTag, unsigned int reqSlotTag, unsigned int reqCode, unsigned int reqStatus)
{
	NVME_COMPLETION nvmeCPL;
	NAND_OPERATION_RESULT nandOperationResult;

	//NAND operation result decision
	nandOperationResult = NAND_RESULT_UNDEFINED;
	switch(reqCode)
	{
	case REQ_CODE_WRITE:
		if(reqStatus == REQ_STATUS_DONE)
			nandOperationResult = NAND_RESULT_DONE;
		else if(reqStatus == REQ_STATUS_FAIL)
			nandOperationResult = NAND_RESULT_PROGRAM_FAIL;
		break;
	case REQ_CODE_READ:
		if(reqStatus == REQ_STATUS_FAIL)
			nandOperationResult = NAND_RESULT_READ_FAIL_TRIGGER;
		break;
	case REQ_CODE_READ_TRANSFER:
		if(reqStatus == REQ_STATUS_DONE)
			nandOperationResult = NAND_RESULT_DONE;
		else if(reqStatus == REQ_STATUS_WARNING)
			nandOperationResult = NAND_RESULT_READ_DONE_UNCORRECTABLE_SOON;
		else if(reqStatus == REQ_STATUS_FAIL)
			nandOperationResult = NAND_RESULT_READ_FAIL_TRANSFER;
		break;
	case REQ_CODE_ERASE:
		if(reqStatus == REQ_STATUS_DONE)
			nandOperationResult = NAND_RESULT_DONE;
		else if(reqStatus == REQ_STATUS_FAIL)
			nandOperationResult = NAND_RESULT_ERASE_FAIL;
		break;
	}

	//set fail flag when error occurs
	if((nandOperationResult != NAND_RESULT_DONE) && (nandOperationResult != NAND_RESULT_READ_DONE_UNCORRECTABLE_SOON))
		nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].fail = 1;

	if(reqCode == REQ_CODE_WRITE)
	{
		nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].notCompletedNANDWriteCount--;
#if (PRINT_DEBUG_MSG_FUA == 1)
		xil_printf("Decrease io NAND Write FUA CmdSlotTag %d reqSlotTag %d reqCode %d dataBuffEntry %d\r\n",
				cmdSlotTag, reqSlotTag, reqCode, reqPoolPtr->reqPool[reqSlotTag].dataBufInfo.entry);
#endif
		if((nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].notCompletedRxCount == 0)
					&&(nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].notCompletedNANDWriteCount == 0))
		{
			nvmeCPL.dword[0] = 0;
			nvmeCPL.specific = 0x0;
			nvmeCPL.statusFieldWord = 0;
			nvmeCPL.statusField.DNR = 1;

			if(nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].fail)
			{
				if(reqCode == REQ_CODE_WRITE)
				{
					nvmeCPL.statusField.SCT = SCT_MEDIA_AND_DATA_INTEGRITY_ERRORS;
					nvmeCPL.statusField.SC = SC_WRITE_FAULT;
				}
				else if((reqCode == REQ_CODE_READ) || (reqCode == REQ_CODE_READ_TRANSFER))
				{
					nvmeCPL.statusField.SCT = SCT_MEDIA_AND_DATA_INTEGRITY_ERRORS;
					nvmeCPL.statusField.SC = SC_UNRECOVERED_READ_ERROR;
				}
				else if(reqCode ==  REQ_CODE_ERASE)
				{
					nvmeCPL.statusField.SCT = SCT_MEDIA_AND_DATA_INTEGRITY_ERRORS;
					nvmeCPL.statusField.SC = SC_ACCESS_DENIED;
				}
			}
			else
			{
				nvmeCPL.statusField.SCT = SCT_GENERIC_COMMAND_STATUS;
				nvmeCPL.statusField.SC = SC_SUCCESSFUL_COMPLETION;
			}
			set_nvme_cpl(GetQIDNvmeIoCmd(cmdSlotTag), GetCIDNvmeIoCmd(cmdSlotTag), nvmeCPL.specific, nvmeCPL.statusFieldWord);
			set_nvme_slot_release(cmdSlotTag);
			ResetFUANvmeIoCmd(cmdSlotTag, reqSlotTag);
#if (PRINT_DEBUG_MSG_FUA == 1)
			if(nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].fail==1)
			{
				xil_printf("Failed NAND execute for Rx FUA CmdSlotTag %d reqSlotTag %d reqCode %d dataBuffEntry %d reqStatus %d\r\n",
						cmdSlotTag, reqSlotTag, reqCode, reqPoolPtr->reqPool[reqSlotTag].dataBufInfo.entry, reqStatus);
			}
			else
			{
				xil_printf("Complete Rx FUA CmdSlotTag %d reqSlotTag %d reqCode %d dataBuffEntry %d\r\n",
						cmdSlotTag, reqSlotTag, reqCode, reqPoolPtr->reqPool[reqSlotTag].dataBufInfo.entry);
			}
#endif
		}
		else
		{
#if (PRINT_DEBUG_MSG_FUA == 1)
			//xil_printf("Hold Rx (for NAND Write) FUA CmdSlotTag %d reqSlotTag %d reqCode %d dataBuffEntry %d\r\n",
			//		cmdSlotTag, reqSlotTag, reqCode, reqPoolPtr->reqPool[reqSlotTag].dataBufInfo.entry);
#endif
		}
	}
	else if((reqCode == REQ_CODE_READ)||(reqCode == REQ_CODE_READ_TRANSFER))
	{
		nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].notCompletedNANDReadCount--;
#if (PRINT_DEBUG_MSG_FUA == 1)
		xil_printf("Decrease io NAND Read FUA CmdSlotTag %d reqSlotTag %d reqCode %d dataBuffEntry %d\r\n",
				cmdSlotTag, reqSlotTag, reqCode, reqPoolPtr->reqPool[reqSlotTag].dataBufInfo.entry);
#endif
	}
}
