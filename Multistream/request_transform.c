//////////////////////////////////////////////////////////////////////////////////
// request_transform.c for Cosmos+ OpenSSD
// Copyright (c) 2017 Hanyang University ENC Lab.
// Contributed by Yong Ho Song <yhsong@enc.hanyang.ac.kr>
//				  Jaewook Kwak <jwkwak@enc.hanyang.ac.kr>
//			      Sangjin Lee <sjlee@enc.hanyang.ac.kr>
//
// This file is part of Cosmos+ OpenSSD.
//
// Cosmos+ OpenSSD is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3, or (at your option)
// any later version.
//
// Cosmos+ OpenSSD is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Cosmos+ OpenSSD; see the file COPYING.
// If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
// Company: ENC Lab. <http://enc.hanyang.ac.kr>
// Engineer: Jaewook Kwak <jwkwak@enc.hanyang.ac.kr>
//
// Project Name: Cosmos+ OpenSSD
// Design Name: Cosmos+ Firmware
// Module Name: Request Scheduler
// File Name: request_transform.c
//
// Version: v1.0.0
//
// Description:
//	 - transform request information
//   - check dependency between requests
//   - issue host DMA request to host DMA engine
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
// Revision History:
//
// * v1.0.0
//   - First draft
//////////////////////////////////////////////////////////////////////////////////


#include "nvme/nvme_main.h"
#include "memory_map.h"
#include "request_transform.h"

P_ROW_ADDR_DEPENDENCY_TABLE rowAddrDependencyTablePtr;

void InitDependencyTable()
{
	unsigned int blockNo, wayNo, chNo;
	rowAddrDependencyTablePtr = (P_ROW_ADDR_DEPENDENCY_TABLE)ROW_ADDR_DEPENDENCY_TABLE_ADDR;

	for(blockNo=0 ; blockNo<MAIN_BLOCKS_PER_DIE ; blockNo++)
	{
		for(wayNo=0 ; wayNo<USER_WAYS ; wayNo++)
		{
			for(chNo=0 ; chNo<USER_CHANNELS ; chNo++)
			{
				rowAddrDependencyTablePtr->block[chNo][wayNo][blockNo].permittedProgPage = 0;
				rowAddrDependencyTablePtr->block[chNo][wayNo][blockNo].blockedReadReqCnt = 0;
				rowAddrDependencyTablePtr->block[chNo][wayNo][blockNo].blockedEraseReqFlag = 0;
			}
		}
	}
}

void ReqTransNvmeToSlice(unsigned int cmdSlotTag, unsigned int qID, unsigned int cID, unsigned int startLba, unsigned int nlb, unsigned int cmdCode, unsigned int fua, unsigned int stream_id)
{
	unsigned int reqSlotTag, requestedNvmeBlock, tempNumOfNvmeBlock, transCounter, tempLsa, loop, nvmeBlockOffset, nvmeDmaStartIndex, reqCode;

	if(NVME_BLOCKS_PER_SLICE == 4)
	{
		requestedNvmeBlock = nlb + 1;
		transCounter = 0;
		nvmeDmaStartIndex = 0;
		tempLsa = startLba / NVME_BLOCKS_PER_SLICE;
		loop = ((startLba % NVME_BLOCKS_PER_SLICE) + requestedNvmeBlock) / NVME_BLOCKS_PER_SLICE;

		if(cmdCode == IO_NVM_WRITE)
			reqCode = REQ_CODE_WRITE;
		else if(cmdCode == IO_NVM_READ)
			reqCode = REQ_CODE_READ;
		else
			assert(!"[WARNING] Not supported command code [WARNING]");

		AllocateHostReqTime(cmdSlotTag, reqCode);

	#if (PRINT_DEBUG_MSG_FUA == 1)
		if(fua == REQ_OPT_FORCE_UNIT_ACCESS_ON)
		{
			if(reqCode == REQ_CODE_WRITE)
				xil_printf("IO CMD FUA Write cmdSlotTag %d StartLba %d NvmeBlock %d\r\n", cmdSlotTag, startLba, requestedNvmeBlock);
			else if(reqCode == REQ_CODE_READ)
				xil_printf("IO CMD FUA Read cmdSlotTag %d StartLba %d NvmeBlock %d\r\n", cmdSlotTag, startLba, requestedNvmeBlock);
			else
				assert(!"[WARNING] Not supported command code [WARNING]");
		}
		else
		{
			if(reqCode == REQ_CODE_WRITE)
				xil_printf("IO CMD Write cmdSlotTag %d StartLba %d NvmeBlock %d\r\n", cmdSlotTag, startLba, requestedNvmeBlock);
			else if(reqCode == REQ_CODE_READ)
				xil_printf("IO CMD Read cmdSlotTag %d StartLba %d NvmeBlock %d\r\n", cmdSlotTag, startLba, requestedNvmeBlock);
			else
				assert(!"[WARNING] Not supported command code [WARNING]");
		}
	#endif
		UpdatePerformanceCounterForCompletedNvmeIoReq();

		//first transform
		nvmeBlockOffset = (startLba % NVME_BLOCKS_PER_SLICE);
		if(loop)
			tempNumOfNvmeBlock = NVME_BLOCKS_PER_SLICE - nvmeBlockOffset;
		else
			tempNumOfNvmeBlock = requestedNvmeBlock;

		reqSlotTag = GetFromFreeReqQ();

		reqPoolPtr->reqPool[reqSlotTag].reqType = REQ_TYPE_SLICE;
		reqPoolPtr->reqPool[reqSlotTag].reqCode = reqCode;
		reqPoolPtr->reqPool[reqSlotTag].nvmeCmdSlotTag = cmdSlotTag;
		reqPoolPtr->reqPool[reqSlotTag].qID = qID;
		reqPoolPtr->reqPool[reqSlotTag].cID = cID;
		reqPoolPtr->reqPool[reqSlotTag].logicalSliceAddr = tempLsa;
		reqPoolPtr->reqPool[reqSlotTag].nvmeDmaInfo.startIndex = nvmeDmaStartIndex;
		reqPoolPtr->reqPool[reqSlotTag].nvmeDmaInfo.nvmeBlockOffset = nvmeBlockOffset;
		reqPoolPtr->reqPool[reqSlotTag].nvmeDmaInfo.numOfNvmeBlock = tempNumOfNvmeBlock;
		reqPoolPtr->reqPool[reqSlotTag].nvmeDmaInfo.issuedFlag = REQ_INFO_ISSUED_FLAG_OFF;
		reqPoolPtr->reqPool[reqSlotTag].reqOpt.forceUnitAccess = fua;
		// (jhpark)
		reqPoolPtr->reqPool[reqSlotTag].stream_id = stream_id;


		PutToSliceReqQ(reqSlotTag);

		tempLsa++;
		transCounter++;
		nvmeDmaStartIndex += tempNumOfNvmeBlock;

		if(cmdCode == IO_NVM_WRITE) {
			g_ftl_num_host_write++;
		}

		//transform continue
		while(transCounter < loop)
		{
			nvmeBlockOffset = 0;
			tempNumOfNvmeBlock = NVME_BLOCKS_PER_SLICE;

			reqSlotTag = GetFromFreeReqQ();

			reqPoolPtr->reqPool[reqSlotTag].reqType = REQ_TYPE_SLICE;
			reqPoolPtr->reqPool[reqSlotTag].reqCode = reqCode;
			reqPoolPtr->reqPool[reqSlotTag].nvmeCmdSlotTag = cmdSlotTag;
			reqPoolPtr->reqPool[reqSlotTag].qID = qID;
			reqPoolPtr->reqPool[reqSlotTag].cID = cID;
			reqPoolPtr->reqPool[reqSlotTag].logicalSliceAddr = tempLsa;
			reqPoolPtr->reqPool[reqSlotTag].nvmeDmaInfo.startIndex = nvmeDmaStartIndex;
			reqPoolPtr->reqPool[reqSlotTag].nvmeDmaInfo.nvmeBlockOffset = nvmeBlockOffset;
			reqPoolPtr->reqPool[reqSlotTag].nvmeDmaInfo.numOfNvmeBlock = tempNumOfNvmeBlock;
			reqPoolPtr->reqPool[reqSlotTag].nvmeDmaInfo.issuedFlag = REQ_INFO_ISSUED_FLAG_OFF;
			reqPoolPtr->reqPool[reqSlotTag].reqOpt.forceUnitAccess = fua;
			// (jhpark)
			reqPoolPtr->reqPool[reqSlotTag].stream_id = stream_id;

			PutToSliceReqQ(reqSlotTag);

			tempLsa++;
			transCounter++;
			nvmeDmaStartIndex += tempNumOfNvmeBlock;

			if(cmdCode == IO_NVM_WRITE) {
				g_ftl_num_host_write++;
			}
		}

		//last transform
		nvmeBlockOffset = 0;
		tempNumOfNvmeBlock = (startLba + requestedNvmeBlock) % NVME_BLOCKS_PER_SLICE;
		if((tempNumOfNvmeBlock == 0) || (loop == 0))
			return ;

		reqSlotTag = GetFromFreeReqQ();

		reqPoolPtr->reqPool[reqSlotTag].reqType = REQ_TYPE_SLICE;
		reqPoolPtr->reqPool[reqSlotTag].reqCode = reqCode;
		reqPoolPtr->reqPool[reqSlotTag].nvmeCmdSlotTag = cmdSlotTag;
		reqPoolPtr->reqPool[reqSlotTag].qID = qID;
		reqPoolPtr->reqPool[reqSlotTag].cID = cID;
		reqPoolPtr->reqPool[reqSlotTag].logicalSliceAddr = tempLsa;
		reqPoolPtr->reqPool[reqSlotTag].nvmeDmaInfo.startIndex = nvmeDmaStartIndex;
		reqPoolPtr->reqPool[reqSlotTag].nvmeDmaInfo.nvmeBlockOffset = nvmeBlockOffset;
		reqPoolPtr->reqPool[reqSlotTag].nvmeDmaInfo.numOfNvmeBlock = tempNumOfNvmeBlock;
		reqPoolPtr->reqPool[reqSlotTag].nvmeDmaInfo.issuedFlag = REQ_INFO_ISSUED_FLAG_OFF;
		reqPoolPtr->reqPool[reqSlotTag].reqOpt.forceUnitAccess = fua;
		// (jhpark)
		reqPoolPtr->reqPool[reqSlotTag].stream_id = stream_id;

		PutToSliceReqQ(reqSlotTag);
	}
	else if(NVME_BLOCKS_PER_SLICE == 1)
	{
		requestedNvmeBlock = nlb + 1;
		nvmeDmaStartIndex = 0;
		tempLsa = startLba;
		loop = requestedNvmeBlock;

		if(cmdCode == IO_NVM_WRITE)
			reqCode = REQ_CODE_WRITE;
		else if(cmdCode == IO_NVM_READ)
			reqCode = REQ_CODE_READ;
		else
			assert(!"[WARNING] Not supported command code [WARNING]");

		AllocateHostReqTime(cmdSlotTag, reqCode);
		UpdatePerformanceCounterForCompletedNvmeIoReq();

		for(transCounter = 0; transCounter < loop; transCounter++)
		{
			reqSlotTag = GetFromFreeReqQ();

			reqPoolPtr->reqPool[reqSlotTag].reqType = REQ_TYPE_SLICE;
			reqPoolPtr->reqPool[reqSlotTag].reqCode = reqCode;
			reqPoolPtr->reqPool[reqSlotTag].nvmeCmdSlotTag = cmdSlotTag;
			reqPoolPtr->reqPool[reqSlotTag].qID = qID;
			reqPoolPtr->reqPool[reqSlotTag].cID = cID;
			reqPoolPtr->reqPool[reqSlotTag].logicalSliceAddr = tempLsa;
			reqPoolPtr->reqPool[reqSlotTag].nvmeDmaInfo.startIndex = nvmeDmaStartIndex;
			reqPoolPtr->reqPool[reqSlotTag].nvmeDmaInfo.nvmeBlockOffset = 0;
			reqPoolPtr->reqPool[reqSlotTag].nvmeDmaInfo.numOfNvmeBlock = 1;
			reqPoolPtr->reqPool[reqSlotTag].nvmeDmaInfo.issuedFlag = REQ_INFO_ISSUED_FLAG_OFF;
			reqPoolPtr->reqPool[reqSlotTag].reqOpt.forceUnitAccess = fua;
			// (jhpark)
			reqPoolPtr->reqPool[reqSlotTag].stream_id = stream_id;

			PutToSliceReqQ(reqSlotTag);

			tempLsa++;
			nvmeDmaStartIndex++;
		}
	}
	else
		assert(!"[WARNING] Not supported NVME_BLOCKS_PER_SLICE [WARNING]");

	if(cmdCode == IO_NVM_WRITE) {
		g_ftl_num_host_write++;
	}
}

void EvictDataBufEntry(unsigned int originReqSlotTag)
{
	unsigned int reqSlotTag, virtualSliceAddr, dataBufEntry;

	dataBufEntry = reqPoolPtr->reqPool[originReqSlotTag].dataBufInfo.entry;
	if(dataBufMapPtr->dataBuf[dataBufEntry].dirty == DATA_BUF_DIRTY)
	{
		reqSlotTag = GetFromFreeReqQ();
		virtualSliceAddr =  AddrTransWrite(dataBufMapPtr->dataBuf[dataBufEntry].logicalSliceAddr , reqPoolPtr->reqPool[originReqSlotTag].stream_id);

		reqPoolPtr->reqPool[reqSlotTag].reqType = REQ_TYPE_NAND;
		reqPoolPtr->reqPool[reqSlotTag].reqCode = REQ_CODE_WRITE;
		reqPoolPtr->reqPool[reqSlotTag].nvmeCmdSlotTag = reqPoolPtr->reqPool[originReqSlotTag].nvmeCmdSlotTag;
		reqPoolPtr->reqPool[reqSlotTag].qID = reqPoolPtr->reqPool[originReqSlotTag].qID;
		reqPoolPtr->reqPool[reqSlotTag].cID = reqPoolPtr->reqPool[originReqSlotTag].cID;
		reqPoolPtr->reqPool[reqSlotTag].logicalSliceAddr = dataBufMapPtr->dataBuf[dataBufEntry].logicalSliceAddr;


		reqPoolPtr->reqPool[reqSlotTag].reqOpt.dataBufFormat = REQ_OPT_DATA_BUF_ENTRY;
		reqPoolPtr->reqPool[reqSlotTag].reqOpt.nandAddr = REQ_OPT_NAND_ADDR_VSA;
		reqPoolPtr->reqPool[reqSlotTag].reqOpt.nandEcc = REQ_OPT_NAND_ECC_ON;
		reqPoolPtr->reqPool[reqSlotTag].reqOpt.nandEccWarning = REQ_OPT_NAND_ECC_WARNING_ON;
		reqPoolPtr->reqPool[reqSlotTag].reqOpt.rowAddrDependencyCheck = REQ_OPT_ROW_ADDR_DEPENDENCY_CHECK;
		reqPoolPtr->reqPool[reqSlotTag].reqOpt.blockSpace = REQ_OPT_BLOCK_SPACE_MAIN;
		reqPoolPtr->reqPool[reqSlotTag].reqOpt.forceUnitAccess = reqPoolPtr->reqPool[originReqSlotTag].reqOpt.forceUnitAccess;

		reqPoolPtr->reqPool[reqSlotTag].nandInfo.virtualSliceAddr = virtualSliceAddr;
		reqPoolPtr->reqPool[reqSlotTag].dataBufInfo.entry = dataBufEntry;
		UpdateDataBufEntryInfoBlockingReq(dataBufEntry, reqSlotTag);

		if(reqPoolPtr->reqPool[originReqSlotTag].reqOpt.forceUnitAccess == REQ_OPT_FORCE_UNIT_ACCESS_ON)
			AllocateNotCompletedNandWriteforNvmeIoCmd(reqPoolPtr->reqPool[reqSlotTag].nvmeCmdSlotTag, reqSlotTag, reqPoolPtr->reqPool[reqSlotTag].dataBufInfo.entry, GenerateDataBufAddr(reqSlotTag));

		SelectLowLevelReqQ(reqSlotTag);

		dataBufMapPtr->dataBuf[dataBufEntry].dirty = DATA_BUF_CLEAN;

		AllocateNandReqCntForBufferEviction(reqPoolPtr->reqPool[reqSlotTag].nvmeCmdSlotTag);
	}
}

void DataReadFromNand(unsigned int originReqSlotTag)
{
	unsigned int reqSlotTag, virtualSliceAddr;

	virtualSliceAddr =  AddrTransRead(reqPoolPtr->reqPool[originReqSlotTag].logicalSliceAddr);

	if(virtualSliceAddr != VSA_FAIL)
	{
		reqSlotTag = GetFromFreeReqQ();

		reqPoolPtr->reqPool[reqSlotTag].reqType = REQ_TYPE_NAND;
		reqPoolPtr->reqPool[reqSlotTag].reqCode = REQ_CODE_READ;
		reqPoolPtr->reqPool[reqSlotTag].nvmeCmdSlotTag = reqPoolPtr->reqPool[originReqSlotTag].nvmeCmdSlotTag;
		reqPoolPtr->reqPool[reqSlotTag].qID = reqPoolPtr->reqPool[originReqSlotTag].qID;
		reqPoolPtr->reqPool[reqSlotTag].cID = reqPoolPtr->reqPool[originReqSlotTag].cID;
		reqPoolPtr->reqPool[reqSlotTag].logicalSliceAddr = reqPoolPtr->reqPool[originReqSlotTag].logicalSliceAddr;


		reqPoolPtr->reqPool[reqSlotTag].reqOpt.dataBufFormat = REQ_OPT_DATA_BUF_ENTRY;
		reqPoolPtr->reqPool[reqSlotTag].reqOpt.nandAddr = REQ_OPT_NAND_ADDR_VSA;
		reqPoolPtr->reqPool[reqSlotTag].reqOpt.nandEcc = REQ_OPT_NAND_ECC_ON;
		reqPoolPtr->reqPool[reqSlotTag].reqOpt.nandEccWarning = REQ_OPT_NAND_ECC_WARNING_ON;
		reqPoolPtr->reqPool[reqSlotTag].reqOpt.rowAddrDependencyCheck = REQ_OPT_ROW_ADDR_DEPENDENCY_CHECK;
		reqPoolPtr->reqPool[reqSlotTag].reqOpt.blockSpace = REQ_OPT_BLOCK_SPACE_MAIN;
		reqPoolPtr->reqPool[reqSlotTag].reqOpt.forceUnitAccess = reqPoolPtr->reqPool[originReqSlotTag].reqOpt.forceUnitAccess;

		reqPoolPtr->reqPool[reqSlotTag].nandInfo.virtualSliceAddr = virtualSliceAddr;
		reqPoolPtr->reqPool[reqSlotTag].dataBufInfo.entry = reqPoolPtr->reqPool[originReqSlotTag].dataBufInfo.entry;
		UpdateDataBufEntryInfoBlockingReq(reqPoolPtr->reqPool[reqSlotTag].dataBufInfo.entry, reqSlotTag);

		if(reqPoolPtr->reqPool[originReqSlotTag].reqOpt.forceUnitAccess == REQ_OPT_FORCE_UNIT_ACCESS_ON)
			AllocateNotCompletedNandReadforNvmeIoCmd(reqPoolPtr->reqPool[reqSlotTag].nvmeCmdSlotTag, reqSlotTag, reqPoolPtr->reqPool[reqSlotTag].dataBufInfo.entry, GenerateDataBufAddr(reqSlotTag));

		SelectLowLevelReqQ(reqSlotTag);
	}
}


void ReqTransSliceToLowLevel()
{
	unsigned int reqSlotTag, dataBufEntry;
	unsigned int normalBufEntry, customBufEntry;

	while(sliceReqQ.headReq != REQ_SLOT_TAG_NONE)
	{
		reqSlotTag = GetFromSliceReqQ();
		if(reqSlotTag == REQ_SLOT_TAG_FAIL)
			return ;

		normalBufEntry = CheckDataBufHit(reqSlotTag);

		if(normalBufEntry != DATA_BUF_FAIL)
		{
			dataBufEntry = AllocateDataBufHit(reqSlotTag);

			if(normalBufEntry != dataBufEntry)
				assert("[WARNING] Wrong buffer allocation! [WARNING]\r\n");
#if (PRINT_DEBUG_MSG_FUA == 1)
			if(reqPoolPtr->reqPool[reqSlotTag].reqOpt.forceUnitAccess == REQ_OPT_FORCE_UNIT_ACCESS_ON)
				xil_printf("Hit data buffer reqSlotTag %d dataBuffEntry %d\r\n", reqSlotTag, dataBufEntry);
#endif
			//Data buffer hit
			reqPoolPtr->reqPool[reqSlotTag].dataBufInfo.entry = dataBufEntry;

			if(reqPoolPtr->reqPool[reqSlotTag].reqOpt.forceUnitAccess == REQ_OPT_FORCE_UNIT_ACCESS_ON)
			{
				if(reqPoolPtr->reqPool[reqSlotTag].reqCode == REQ_CODE_READ)
				{
					EvictDataBufEntry(reqSlotTag);
					DataReadFromNand(reqSlotTag);
				}
			}


			UpdatePerformanceCounterForDataBuffHit();
		}
		else
		{
			//Data buffer miss, allocate a new buffer entry
			dataBufEntry = AllocateDataBufMiss();
			reqPoolPtr->reqPool[reqSlotTag].dataBufInfo.entry = dataBufEntry;

#if (PRINT_DEBUG_MSG_FUA == 1)
			if(reqPoolPtr->reqPool[reqSlotTag].reqOpt.forceUnitAccess == REQ_OPT_FORCE_UNIT_ACCESS_ON)
			{
				xil_printf("Miss data buffer reqSlotTag %d dataBufEntry %d\r\n", reqSlotTag, dataBufEntry);
			}
#endif
			//clear the allocated data buffer entry being used by a previous request
			EvictDataBufEntry(reqSlotTag);
			//update meta-data of the allocated data buffer entry
			dataBufMapPtr->dataBuf[dataBufEntry].logicalSliceAddr = reqPoolPtr->reqPool[reqSlotTag].logicalSliceAddr;
			PutToDataBufHashList(dataBufEntry);

			if(reqPoolPtr->reqPool[reqSlotTag].reqCode  == REQ_CODE_READ)
			{
				DataReadFromNand(reqSlotTag);
			}
			else if(reqPoolPtr->reqPool[reqSlotTag].reqCode  == REQ_CODE_WRITE)
			{
				if(reqPoolPtr->reqPool[reqSlotTag].nvmeDmaInfo.numOfNvmeBlock != NVME_BLOCKS_PER_SLICE) //for read modify write
				{
					DataReadFromNand(reqSlotTag);
					UpdatePerformanceCounterForReadModifyWrite();
				}
			}
		}

		//transform this slice request to nvme request
		if(reqPoolPtr->reqPool[reqSlotTag].reqCode  == REQ_CODE_WRITE)
		{
			dataBufMapPtr->dataBuf[dataBufEntry].dirty = DATA_BUF_DIRTY;
			reqPoolPtr->reqPool[reqSlotTag].reqCode = REQ_CODE_RxDMA;
		}
		else if(reqPoolPtr->reqPool[reqSlotTag].reqCode  == REQ_CODE_READ)
			reqPoolPtr->reqPool[reqSlotTag].reqCode = REQ_CODE_TxDMA;
		else
			assert(!"[WARNING] Not supported reqCode. [WARNING]");

		reqPoolPtr->reqPool[reqSlotTag].reqType = REQ_TYPE_NVME_DMA;
		reqPoolPtr->reqPool[reqSlotTag].reqOpt.dataBufFormat = REQ_OPT_DATA_BUF_ENTRY;
		UpdateDataBufEntryInfoBlockingReq(dataBufEntry, reqSlotTag);

		if(reqPoolPtr->reqPool[reqSlotTag].reqOpt.forceUnitAccess == REQ_OPT_FORCE_UNIT_ACCESS_ON)
		{
			SetFUANvmeIoCmd(reqPoolPtr->reqPool[reqSlotTag].nvmeCmdSlotTag, reqSlotTag, reqPoolPtr->reqPool[reqSlotTag].qID, reqPoolPtr->reqPool[reqSlotTag].cID);
			if(reqPoolPtr->reqPool[reqSlotTag].reqCode == REQ_CODE_RxDMA)
			{
				AllocateNotCompletedRxforNvmeIoCmd(reqPoolPtr->reqPool[reqSlotTag].nvmeCmdSlotTag, reqPoolPtr->reqPool[reqSlotTag].dataBufInfo.entry, GenerateDataBufAddr(reqSlotTag));
				AllocateNotIssuedRxforNvmeIoCmd(reqPoolPtr->reqPool[reqSlotTag].nvmeCmdSlotTag, reqPoolPtr->reqPool[reqSlotTag].dataBufInfo.entry, GenerateDataBufAddr(reqSlotTag));
			}
			else if(reqPoolPtr->reqPool[reqSlotTag].reqCode == REQ_CODE_TxDMA)
			{
				AllocateNotCompletedTxforNvmeIoCmd(reqPoolPtr->reqPool[reqSlotTag].nvmeCmdSlotTag, reqPoolPtr->reqPool[reqSlotTag].dataBufInfo.entry, GenerateDataBufAddr(reqSlotTag));
				AllocateNotIssuedTxforNvmeIoCmd(reqPoolPtr->reqPool[reqSlotTag].nvmeCmdSlotTag, reqPoolPtr->reqPool[reqSlotTag].dataBufInfo.entry, GenerateDataBufAddr(reqSlotTag));
			}
		}

		if(reqPoolPtr->reqPool[reqSlotTag].reqOpt.forceUnitAccess == REQ_OPT_FORCE_UNIT_ACCESS_ON)	//compulsory access to nand device
		{
			if(reqPoolPtr->reqPool[reqSlotTag].reqCode == REQ_CODE_RxDMA)
			{
				//Data buffer allocated - Rx DMA - NAND write - completion
				EvictDataBufEntry(reqSlotTag);
			}
			else if(reqPoolPtr->reqPool[reqSlotTag].reqCode == REQ_CODE_TxDMA)
			{
				//Data buffer allocated - NAND read - Tx DMA - completion
			}
		}
		SelectLowLevelReqQ(reqSlotTag);
	}
}

unsigned int CheckBufDep(unsigned int reqSlotTag)
{
	if(reqPoolPtr->reqPool[reqSlotTag].prevBlockingReq == REQ_SLOT_TAG_NONE)
		return BUF_DEPENDENCY_REPORT_PASS;
	else
		return BUF_DEPENDENCY_REPORT_BLOCKED;
}

unsigned int CheckRowAddrDep(unsigned int reqSlotTag, unsigned int checkRowAddrDepOpt)
{
	unsigned int dieNo,chNo, wayNo, blockNo, pageNo;

	if(reqPoolPtr->reqPool[reqSlotTag].reqOpt.nandAddr == REQ_OPT_NAND_ADDR_VSA)
	{
		dieNo = Vsa2VdieTranslation(reqPoolPtr->reqPool[reqSlotTag].nandInfo.virtualSliceAddr);
		chNo =  Vdie2PchTranslation(dieNo);
		wayNo = Vdie2PwayTranslation(dieNo);
		blockNo = Vsa2VblockTranslation(reqPoolPtr->reqPool[reqSlotTag].nandInfo.virtualSliceAddr);
		pageNo = Vsa2VpageTranslation(reqPoolPtr->reqPool[reqSlotTag].nandInfo.virtualSliceAddr);
	}
	else
		assert(!"[WARNING] Not supported reqOpt-nandAddress [WARNING]");

	if(reqPoolPtr->reqPool[reqSlotTag].reqCode == REQ_CODE_READ)
	{
		if(checkRowAddrDepOpt == ROW_ADDR_DEPENDENCY_CHECK_OPT_SELECT)
		{
			if(rowAddrDependencyTablePtr->block[chNo][wayNo][blockNo].blockedEraseReqFlag)
				SyncReleaseEraseReq(chNo, wayNo, blockNo);

			if(pageNo < rowAddrDependencyTablePtr->block[chNo][wayNo][blockNo].permittedProgPage)
				return ROW_ADDR_DEPENDENCY_REPORT_PASS;

			rowAddrDependencyTablePtr->block[chNo][wayNo][blockNo].blockedReadReqCnt++;
		}
		else if(checkRowAddrDepOpt == ROW_ADDR_DEPENDENCY_CHECK_OPT_RELEASE)
		{
			if(pageNo < rowAddrDependencyTablePtr->block[chNo][wayNo][blockNo].permittedProgPage)
			{
				rowAddrDependencyTablePtr->block[chNo][wayNo][blockNo].blockedReadReqCnt--;
				return	ROW_ADDR_DEPENDENCY_REPORT_PASS;
			}
		}
		else
			assert(!"[WARNING] Not supported checkRowAddrDepOpt [WARNING]");
	}
	else if(reqPoolPtr->reqPool[reqSlotTag].reqCode == REQ_CODE_WRITE)
	{
		if(pageNo == rowAddrDependencyTablePtr->block[chNo][wayNo][blockNo].permittedProgPage)
		{
			rowAddrDependencyTablePtr->block[chNo][wayNo][blockNo].permittedProgPage++;

			return ROW_ADDR_DEPENDENCY_REPORT_PASS;
		}
	}
	else if(reqPoolPtr->reqPool[reqSlotTag].reqCode == REQ_CODE_ERASE)
	{
		if(rowAddrDependencyTablePtr->block[chNo][wayNo][blockNo].permittedProgPage == reqPoolPtr->reqPool[reqSlotTag].nandInfo.programmedPageCnt)
			if(rowAddrDependencyTablePtr->block[chNo][wayNo][blockNo].blockedReadReqCnt == 0)
			{
				rowAddrDependencyTablePtr->block[chNo][wayNo][blockNo].permittedProgPage = 0;
				rowAddrDependencyTablePtr->block[chNo][wayNo][blockNo].blockedEraseReqFlag = 0;

				return ROW_ADDR_DEPENDENCY_REPORT_PASS;
			}

		if(checkRowAddrDepOpt == ROW_ADDR_DEPENDENCY_CHECK_OPT_SELECT)
			rowAddrDependencyTablePtr->block[chNo][wayNo][blockNo].blockedEraseReqFlag = 1;
		else if(checkRowAddrDepOpt == ROW_ADDR_DEPENDENCY_CHECK_OPT_RELEASE)
		{
			//pass, go to return
		}
		else
			assert(!"[WARNING] Not supported checkRowAddrDepOpt [WARNING]");
	}
	else
		assert(!"[WARNING] Not supported reqCode [WARNING]");

	return ROW_ADDR_DEPENDENCY_REPORT_BLOCKED;
}


unsigned int UpdateRowAddrDepTableForBufBlockedReq(unsigned int reqSlotTag)
{
	unsigned int dieNo, chNo, wayNo, blockNo, pageNo, bufDepCheckReport;

	if(reqPoolPtr->reqPool[reqSlotTag].reqOpt.nandAddr == REQ_OPT_NAND_ADDR_VSA)
	{
		dieNo = Vsa2VdieTranslation(reqPoolPtr->reqPool[reqSlotTag].nandInfo.virtualSliceAddr);
		chNo =  Vdie2PchTranslation(dieNo);
		wayNo = Vdie2PwayTranslation(dieNo);
		blockNo = Vsa2VblockTranslation(reqPoolPtr->reqPool[reqSlotTag].nandInfo.virtualSliceAddr);
		pageNo = Vsa2VpageTranslation(reqPoolPtr->reqPool[reqSlotTag].nandInfo.virtualSliceAddr);
	}
	else
		assert(!"[WARNING] Not supported reqOpt-nandAddress [WARNING]");

	if(reqPoolPtr->reqPool[reqSlotTag].reqCode == REQ_CODE_READ)
	{
		if(rowAddrDependencyTablePtr->block[chNo][wayNo][blockNo].blockedEraseReqFlag)
		{
			SyncReleaseEraseReq(chNo, wayNo, blockNo);

			bufDepCheckReport = CheckBufDep(reqSlotTag);
			if(bufDepCheckReport == BUF_DEPENDENCY_REPORT_PASS)
			{
				if(pageNo < rowAddrDependencyTablePtr->block[chNo][wayNo][blockNo].permittedProgPage)
					PutToNandReqQ(reqSlotTag, chNo, wayNo);
				else
				{
					rowAddrDependencyTablePtr->block[chNo][wayNo][blockNo].blockedReadReqCnt++;
					PutToBlockedByRowAddrDepReqQ(reqSlotTag, chNo, wayNo);
				}

				return ROW_ADDR_DEPENDENCY_TABLE_UPDATE_REPORT_SYNC;
			}
		}
		rowAddrDependencyTablePtr->block[chNo][wayNo][blockNo].blockedReadReqCnt++;
	}
	else if(reqPoolPtr->reqPool[reqSlotTag].reqCode == REQ_CODE_ERASE)
		rowAddrDependencyTablePtr->block[chNo][wayNo][blockNo].blockedEraseReqFlag = 1;

	return ROW_ADDR_DEPENDENCY_TABLE_UPDATE_REPORT_DONE;
}

void SelectLowLevelReqQ(unsigned int reqSlotTag)
{
	unsigned int dieNo, chNo, wayNo, bufDepCheckReport, rowAddrDepCheckReport, rowAddrDepTableUpdateReport;

	bufDepCheckReport = CheckBufDep(reqSlotTag);
	if(bufDepCheckReport == BUF_DEPENDENCY_REPORT_PASS)
	{
		if(reqPoolPtr->reqPool[reqSlotTag].reqType  == REQ_TYPE_NVME_DMA)
		{
			IssueNvmeDmaReq(reqSlotTag);
			PutToNvmeDmaReqQ(reqSlotTag);
		}
		else if(reqPoolPtr->reqPool[reqSlotTag].reqType  == REQ_TYPE_NAND)
		{
			if(reqPoolPtr->reqPool[reqSlotTag].reqOpt.nandAddr == REQ_OPT_NAND_ADDR_VSA)
			{
				dieNo = Vsa2VdieTranslation(reqPoolPtr->reqPool[reqSlotTag].nandInfo.virtualSliceAddr);
				chNo =  Vdie2PchTranslation(dieNo);
				wayNo = Vdie2PwayTranslation(dieNo);
			}
			else if(reqPoolPtr->reqPool[reqSlotTag].reqOpt.nandAddr == REQ_OPT_NAND_ADDR_PHY_ORG)
			{
				chNo =  reqPoolPtr->reqPool[reqSlotTag].nandInfo.physicalCh;
				wayNo = reqPoolPtr->reqPool[reqSlotTag].nandInfo.physicalWay;
			}
			else
				assert(!"[WARNING] Not supported reqOpt-nandAddress [WARNING]");

			if(reqPoolPtr->reqPool[reqSlotTag].reqOpt.rowAddrDependencyCheck == REQ_OPT_ROW_ADDR_DEPENDENCY_CHECK)
			{
				rowAddrDepCheckReport = CheckRowAddrDep(reqSlotTag, ROW_ADDR_DEPENDENCY_CHECK_OPT_SELECT);

				if(rowAddrDepCheckReport == ROW_ADDR_DEPENDENCY_REPORT_PASS)
					PutToNandReqQ(reqSlotTag, chNo, wayNo);
				else if(rowAddrDepCheckReport == ROW_ADDR_DEPENDENCY_REPORT_BLOCKED)
					PutToBlockedByRowAddrDepReqQ(reqSlotTag, chNo, wayNo);
				else
					assert(!"[WARNING] Not supported report [WARNING]");
			}
			else if(reqPoolPtr->reqPool[reqSlotTag].reqOpt.rowAddrDependencyCheck == REQ_OPT_ROW_ADDR_DEPENDENCY_NONE)
				PutToNandReqQ(reqSlotTag, chNo, wayNo);
			else
				assert(!"[WARNING] Not supported reqOpt [WARNING]");

		}
		else
			assert(!"[WARNING] Not supported reqType [WARNING]");
	}
	else if(bufDepCheckReport == BUF_DEPENDENCY_REPORT_BLOCKED)
	{
		if(reqPoolPtr->reqPool[reqSlotTag].reqType  == REQ_TYPE_NAND)
			if(reqPoolPtr->reqPool[reqSlotTag].reqOpt.rowAddrDependencyCheck == REQ_OPT_ROW_ADDR_DEPENDENCY_CHECK)
			{
				rowAddrDepTableUpdateReport = UpdateRowAddrDepTableForBufBlockedReq(reqSlotTag);

				if(rowAddrDepTableUpdateReport == ROW_ADDR_DEPENDENCY_TABLE_UPDATE_REPORT_DONE)
				{
					//pass, go to PutToBlockedByBufDepReqQ
				}
				else if(rowAddrDepTableUpdateReport == ROW_ADDR_DEPENDENCY_TABLE_UPDATE_REPORT_SYNC)
					return;
				else
					assert(!"[WARNING] Not supported report [WARNING]");
			}

		PutToBlockedByBufDepReqQ(reqSlotTag);
	}
	else
		assert(!"[WARNING] Not supported report [WARNING]");
}


void ReleaseBlockedByBufDepReq(unsigned int reqSlotTag)
{
	unsigned int targetReqSlotTag, dieNo, chNo, wayNo, rowAddrDepCheckReport;

	targetReqSlotTag = REQ_SLOT_TAG_NONE;
	if(reqPoolPtr->reqPool[reqSlotTag].nextBlockingReq != REQ_SLOT_TAG_NONE)
	{
		targetReqSlotTag = reqPoolPtr->reqPool[reqSlotTag].nextBlockingReq;
		reqPoolPtr->reqPool[targetReqSlotTag].prevBlockingReq = REQ_SLOT_TAG_NONE;
		reqPoolPtr->reqPool[reqSlotTag].nextBlockingReq = REQ_SLOT_TAG_NONE;
	}

	if(reqPoolPtr->reqPool[reqSlotTag].reqOpt.dataBufFormat == REQ_OPT_DATA_BUF_ENTRY)
	{
		if(dataBufMapPtr->dataBuf[reqPoolPtr->reqPool[reqSlotTag].dataBufInfo.entry].blockingReqTail == reqSlotTag)
			dataBufMapPtr->dataBuf[reqPoolPtr->reqPool[reqSlotTag].dataBufInfo.entry].blockingReqTail = REQ_SLOT_TAG_NONE;
	}
	else if(reqPoolPtr->reqPool[reqSlotTag].reqOpt.dataBufFormat == REQ_OPT_DATA_BUF_TEMP_ENTRY)
	{
		if(tempDataBufMapPtr->tempDataBuf[reqPoolPtr->reqPool[reqSlotTag].dataBufInfo.entry].blockingReqTail == reqSlotTag)
			tempDataBufMapPtr->tempDataBuf[reqPoolPtr->reqPool[reqSlotTag].dataBufInfo.entry].blockingReqTail = REQ_SLOT_TAG_NONE;
	}

	if((targetReqSlotTag != REQ_SLOT_TAG_NONE) && (reqPoolPtr->reqPool[targetReqSlotTag].reqQueueType == REQ_QUEUE_TYPE_BLOCKED_BY_BUF_DEP))
	{
		SelectiveGetFromBlockedByBufDepReqQ(targetReqSlotTag);

		if(reqPoolPtr->reqPool[targetReqSlotTag].reqType == REQ_TYPE_NVME_DMA)
		{
			IssueNvmeDmaReq(targetReqSlotTag);
			PutToNvmeDmaReqQ(targetReqSlotTag);
		}
		else if(reqPoolPtr->reqPool[targetReqSlotTag].reqType  == REQ_TYPE_NAND)
		{
			if(reqPoolPtr->reqPool[targetReqSlotTag].reqOpt.nandAddr == REQ_OPT_NAND_ADDR_VSA)
			{
				dieNo = Vsa2VdieTranslation(reqPoolPtr->reqPool[targetReqSlotTag].nandInfo.virtualSliceAddr);
				chNo =  Vdie2PchTranslation(dieNo);
				wayNo = Vdie2PwayTranslation(dieNo);
			}
			else
				assert(!"[WARNING] Not supported reqOpt-nandAddress [WARNING]");

			if(reqPoolPtr->reqPool[targetReqSlotTag].reqOpt.rowAddrDependencyCheck == REQ_OPT_ROW_ADDR_DEPENDENCY_CHECK)
			{
				rowAddrDepCheckReport = CheckRowAddrDep(targetReqSlotTag, ROW_ADDR_DEPENDENCY_CHECK_OPT_RELEASE);

				if(rowAddrDepCheckReport == ROW_ADDR_DEPENDENCY_REPORT_PASS)
					PutToNandReqQ(targetReqSlotTag, chNo, wayNo);
				else if(rowAddrDepCheckReport == ROW_ADDR_DEPENDENCY_REPORT_BLOCKED)
					PutToBlockedByRowAddrDepReqQ(targetReqSlotTag, chNo, wayNo);
				else
					assert(!"[WARNING] Not supported report [WARNING]");
			}
			else if(reqPoolPtr->reqPool[targetReqSlotTag].reqOpt.rowAddrDependencyCheck == REQ_OPT_ROW_ADDR_DEPENDENCY_NONE)
				PutToNandReqQ(targetReqSlotTag, chNo, wayNo);
			else
				assert(!"[WARNING] Not supported reqOpt [WARNING]");
		}
	}
}

void ReleaseBlockedByRowAddrDepReq(unsigned int chNo, unsigned int wayNo)
{
	unsigned int reqSlotTag, nextReq, rowAddrDepCheckReport;

	reqSlotTag = blockedByRowAddrDepReqQ[chNo][wayNo].headReq;

	while(reqSlotTag != REQ_SLOT_TAG_NONE)
	{
		nextReq = reqPoolPtr->reqPool[reqSlotTag].nextReq;

		if(reqPoolPtr->reqPool[reqSlotTag].reqOpt.rowAddrDependencyCheck == REQ_OPT_ROW_ADDR_DEPENDENCY_CHECK)
		{
			rowAddrDepCheckReport = CheckRowAddrDep(reqSlotTag, ROW_ADDR_DEPENDENCY_CHECK_OPT_RELEASE);

			if(rowAddrDepCheckReport == ROW_ADDR_DEPENDENCY_REPORT_PASS)
			{
				SelectiveGetFromBlockedByRowAddrDepReqQ(reqSlotTag, chNo, wayNo);
				PutToNandReqQ(reqSlotTag, chNo, wayNo);
			}
			else if(rowAddrDepCheckReport == ROW_ADDR_DEPENDENCY_REPORT_BLOCKED)
			{
				//pass, go to while loop
			}
			else
				assert(!"[WARNING] Not supported report [WARNING]");
		}
		else
			assert(!"[WARNING] Not supported reqOpt [WARNING]");

		reqSlotTag = nextReq;
	}
}

void IssueNvmeDmaReq(unsigned int reqSlotTag)
{
	unsigned int devAddr, dmaIndex, numOfNvmeBlock;

	dmaIndex = reqPoolPtr->reqPool[reqSlotTag].nvmeDmaInfo.startIndex;
	devAddr = GenerateDataBufAddr(reqSlotTag);
	numOfNvmeBlock = 0;

	if(reqPoolPtr->reqPool[reqSlotTag].reqCode == REQ_CODE_RxDMA)
	{
		while(numOfNvmeBlock < reqPoolPtr->reqPool[reqSlotTag].nvmeDmaInfo.numOfNvmeBlock)
		{
			if(reqPoolPtr->reqPool[reqSlotTag].reqOpt.forceUnitAccess == REQ_OPT_FORCE_UNIT_ACCESS_ON)
			{
#if (PRINT_DEBUG_MSG_FUA == 1)
				xil_printf("Issue Rx Nvme Dma FUA cmdSlotTag %d reqSlotTag %d devAddr %08x buffEntry %d\r\n", reqPoolPtr->reqPool[reqSlotTag].nvmeCmdSlotTag, reqSlotTag, devAddr, reqPoolPtr->reqPool[reqSlotTag].dataBufInfo.entry);
#endif
				set_auto_rx_dma(reqPoolPtr->reqPool[reqSlotTag].nvmeCmdSlotTag, dmaIndex, devAddr, NVME_COMMAND_AUTO_COMPLETION_OFF);
				if(numOfNvmeBlock == (reqPoolPtr->reqPool[reqSlotTag].nvmeDmaInfo.numOfNvmeBlock - 1))
					IssuedRxforNvmeIoCmd(reqPoolPtr->reqPool[reqSlotTag].nvmeCmdSlotTag, reqSlotTag, reqPoolPtr->reqPool[reqSlotTag].reqCode);
			}
			else
			{
#if (PRINT_DEBUG_MSG_CUSTOM_CMD == 1)
				xil_printf("Issue Rx Nvme Dma reqSlotTag %d devAddr %08x buffEntry %d\r\n", reqSlotTag, devAddr, reqPoolPtr->reqPool[reqSlotTag].dataBufInfo.entry);
#endif
				set_auto_rx_dma(reqPoolPtr->reqPool[reqSlotTag].nvmeCmdSlotTag, dmaIndex, devAddr, NVME_COMMAND_AUTO_COMPLETION_ON);
				if(numOfNvmeBlock == (reqPoolPtr->reqPool[reqSlotTag].nvmeDmaInfo.numOfNvmeBlock - 1))
					reqPoolPtr->reqPool[reqSlotTag].nvmeDmaInfo.issuedFlag = REQ_INFO_ISSUED_FLAG_ON;
			}

			numOfNvmeBlock++;
			dmaIndex++;
			devAddr += BYTES_PER_NVME_BLOCK;
		}
		reqPoolPtr->reqPool[reqSlotTag].nvmeDmaInfo.reqTail = g_hostDmaStatus.fifoTail.autoDmaRx;
		reqPoolPtr->reqPool[reqSlotTag].nvmeDmaInfo.overFlowCnt = g_hostDmaAssistStatus.autoDmaRxOverFlowCnt;
	}
	else if(reqPoolPtr->reqPool[reqSlotTag].reqCode == REQ_CODE_TxDMA)
	{
		while(numOfNvmeBlock < reqPoolPtr->reqPool[reqSlotTag].nvmeDmaInfo.numOfNvmeBlock)
		{
			if(reqPoolPtr->reqPool[reqSlotTag].reqOpt.forceUnitAccess == REQ_OPT_FORCE_UNIT_ACCESS_ON)
			{
				if(nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[reqPoolPtr->reqPool[reqSlotTag].nvmeCmdSlotTag].notCompletedNANDReadCount == 0)
				{
#if (PRINT_DEBUG_MSG_FUA == 1)
					xil_printf("Issue Tx Nvme Dma FUA cmdSlotTag %d reqSlotTag %d devAddr %08x buffEntry %d\r\n", reqPoolPtr->reqPool[reqSlotTag].nvmeCmdSlotTag, reqSlotTag, devAddr, reqPoolPtr->reqPool[reqSlotTag].dataBufInfo.entry);
#endif
					set_auto_tx_dma(reqPoolPtr->reqPool[reqSlotTag].nvmeCmdSlotTag, dmaIndex, devAddr, NVME_COMMAND_AUTO_COMPLETION_OFF);
					if(numOfNvmeBlock == (reqPoolPtr->reqPool[reqSlotTag].nvmeDmaInfo.numOfNvmeBlock - 1))
						IssuedTxforNvmeIoCmd(reqPoolPtr->reqPool[reqSlotTag].nvmeCmdSlotTag, reqSlotTag, reqPoolPtr->reqPool[reqSlotTag].reqCode);

				}
				else
				{
#if (PRINT_DEBUG_MSG_FUA == 1)
					xil_printf("Hold Issue Tx Nvme Dma FUA cmdSlotTag %d reqSlotTag %d devAddr %08x buffEntry %d\r\n", reqPoolPtr->reqPool[reqSlotTag].nvmeCmdSlotTag, reqSlotTag, devAddr, reqPoolPtr->reqPool[reqSlotTag].dataBufInfo.entry);
#endif
					return;
				}
			}
			else
			{
#if (PRINT_DEBUG_MSG_CUSTOM_CMD == 1)
				xil_printf("Issue Tx Nvme Dma reqSlotTag %d devAddr %08x buffEntry %d\r\n", reqSlotTag, devAddr, reqPoolPtr->reqPool[reqSlotTag].dataBufInfo.entry);
#endif
				set_auto_tx_dma(reqPoolPtr->reqPool[reqSlotTag].nvmeCmdSlotTag, dmaIndex, devAddr, NVME_COMMAND_AUTO_COMPLETION_ON);
				if(numOfNvmeBlock == (reqPoolPtr->reqPool[reqSlotTag].nvmeDmaInfo.numOfNvmeBlock - 1))
					reqPoolPtr->reqPool[reqSlotTag].nvmeDmaInfo.issuedFlag = REQ_INFO_ISSUED_FLAG_ON;
			}
			numOfNvmeBlock++;
			dmaIndex++;
			devAddr += BYTES_PER_NVME_BLOCK;
		}
		reqPoolPtr->reqPool[reqSlotTag].nvmeDmaInfo.reqTail =  g_hostDmaStatus.fifoTail.autoDmaTx;
		reqPoolPtr->reqPool[reqSlotTag].nvmeDmaInfo.overFlowCnt = g_hostDmaAssistStatus.autoDmaTxOverFlowCnt;
	}
	else
		assert(!"[WARNING] Not supported reqCode [WARNING]");
}

void CheckDoneNvmeDmaReq()
{
	unsigned int reqSlotTag, prevReq, cmdSlotTag, bufDepCheckReport;
	unsigned int rxDone, txDone;

	reqSlotTag = nvmeDmaReqQ.tailReq;
	rxDone = 0;
	txDone = 0;

	while(reqSlotTag != REQ_SLOT_TAG_NONE)
	{
		prevReq = reqPoolPtr->reqPool[reqSlotTag].prevReq;
		cmdSlotTag = reqPoolPtr->reqPool[reqSlotTag].nvmeCmdSlotTag;
		if(GetFUANvmeIoCmd(cmdSlotTag) == REQ_OPT_FORCE_UNIT_ACCESS_OFF)
		{
			if(reqPoolPtr->reqPool[reqSlotTag].reqCode  == REQ_CODE_RxDMA)
			{
				if(!rxDone)
					rxDone = check_auto_rx_dma_partial_done(reqPoolPtr->reqPool[reqSlotTag].nvmeDmaInfo.reqTail , reqPoolPtr->reqPool[reqSlotTag].nvmeDmaInfo.overFlowCnt);
				if(rxDone)
					SelectiveGetFromNvmeDmaReqQ(reqSlotTag);
			}
			else
			{
				if(!txDone)
					txDone = check_auto_tx_dma_partial_done(reqPoolPtr->reqPool[reqSlotTag].nvmeDmaInfo.reqTail , reqPoolPtr->reqPool[reqSlotTag].nvmeDmaInfo.overFlowCnt);
				if(txDone)
					SelectiveGetFromNvmeDmaReqQ(reqSlotTag);
			}
		}
		else if(GetFUANvmeIoCmd(cmdSlotTag) == REQ_OPT_FORCE_UNIT_ACCESS_ON)
		{
			if(reqPoolPtr->reqPool[reqSlotTag].reqCode  == REQ_CODE_RxDMA)
			{
				if(reqPoolPtr->reqPool[reqSlotTag].nvmeDmaInfo.issuedFlag == REQ_INFO_ISSUED_FLAG_ON)
				{
					if(!rxDone)
						rxDone = check_auto_rx_dma_partial_done(reqPoolPtr->reqPool[reqSlotTag].nvmeDmaInfo.reqTail , reqPoolPtr->reqPool[reqSlotTag].nvmeDmaInfo.overFlowCnt);
					if(rxDone)
						SelectiveGetFromNvmeDmaReqQ(reqSlotTag);
				}
				else
				{
					bufDepCheckReport = CheckBufDep(reqSlotTag);
					if(bufDepCheckReport == BUF_DEPENDENCY_REPORT_BLOCKED)
						ReleaseBlockedByBufDepReq(reqSlotTag);
					else
						IssueNvmeDmaReq(reqSlotTag);
				}
			}
			else //reqPoolPtr->reqPool[reqSlotTag].reqCode  == REQ_CODE_TxDMA
			{
				if(reqPoolPtr->reqPool[reqSlotTag].nvmeDmaInfo.issuedFlag == REQ_INFO_ISSUED_FLAG_ON)
				{
					if(nvmeIoCmdCompletionTablePtr->nvmeIoCmdCompleteEntry[cmdSlotTag].notCompletedNANDReadCount == 0)
					{
						if(!txDone)
							txDone = check_auto_tx_dma_partial_done(reqPoolPtr->reqPool[reqSlotTag].nvmeDmaInfo.reqTail , reqPoolPtr->reqPool[reqSlotTag].nvmeDmaInfo.overFlowCnt);
						if(txDone)
							SelectiveGetFromNvmeDmaReqQ(reqSlotTag);
					}
				}
				else
				{
					bufDepCheckReport = CheckBufDep(reqSlotTag);
					if(bufDepCheckReport == BUF_DEPENDENCY_REPORT_BLOCKED)
						ReleaseBlockedByBufDepReq(reqSlotTag);
					else
						IssueNvmeDmaReq(reqSlotTag);
				}
			}
		}
		reqSlotTag = prevReq;
	}
}
