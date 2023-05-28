//////////////////////////////////////////////////////////////////////////////////
// nvme_io_cmd.c for Cosmos+ OpenSSD
// Copyright (c) 2016 Hanyang University ENC Lab.
// Contributed by Yong Ho Song <yhsong@enc.hanyang.ac.kr>
//				  Youngjin Jo <yjjo@enc.hanyang.ac.kr>
//				  Sangjin Lee <sjlee@enc.hanyang.ac.kr>
//				  Jaewook Kwak <jwkwak@enc.hanyang.ac.kr>
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
// Engineer: Sangjin Lee <sjlee@enc.hanyang.ac.kr>
//			 Jaewook Kwak <jwkwak@enc.hanyang.ac.kr>
//
// Project Name: Cosmos+ OpenSSD
// Design Name: Cosmos+ Firmware
// Module Name: NVMe IO Command Handler
// File Name: nvme_io_cmd.c
//
// Version: v1.0.1
//
// Description:
//   - handles NVMe IO command
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
// Revision History:
//
// * v1.0.1
//   - header file for buffer is changed from "ia_lru_buffer.h" to "lru_buffer.h"
//
// * v1.0.0
//   - First draft
//////////////////////////////////////////////////////////////////////////////////

#include <features/dealloc.h>
#include "../memory_map.h"
#include "../nvme_io_cmd_completion.h"
#include "nvme_io_cmd.h"
#include <features/stream.h>

void handle_nvme_io_read(unsigned int cmdSlotTag, NVME_IO_COMMAND *nvmeIOCmd, unsigned int qID)
{
	IO_READ_COMMAND_DW12 readInfo12;
	//IO_READ_COMMAND_DW13 readInfo13;
	//IO_READ_COMMAND_DW15 readInfo15;
	unsigned int startLba[2];
	unsigned int nlb, fua, cID;

	readInfo12.dword = nvmeIOCmd->dword[12];
	//readInfo13.dword = nvmeIOCmd->dword[13];
	//readInfo15.dword = nvmeIOCmd->dword[15];

	startLba[0] = nvmeIOCmd->dword[10];
	startLba[1] = nvmeIOCmd->dword[11];
	nlb = readInfo12.NLB;
	fua = readInfo12.FUA;
	cID = nvmeIOCmd->CID;

	ASSERT(startLba[0] < storageCapacity_L && (startLba[1] < STORAGE_CAPACITY_H || startLba[1] == 0));
	ASSERT(nlb < MAX_NUM_OF_NLB);
	ASSERT((nvmeIOCmd->PRP1[0] & 0x3) == 0 && (nvmeIOCmd->PRP2[0] & 0x3) == 0); //error
	ASSERT(nvmeIOCmd->PRP1[1] < 0x10000 && nvmeIOCmd->PRP2[1] < 0x10000);
#if (TEST_MODE_FUA == 1)
	fua = REQ_OPT_FORCE_UNIT_ACCESS_ON;
#endif
#if (TEST_MODE_FUA == 2)
	fua = REQ_OPT_FORCE_UNIT_ACCESS_OFF;
#endif


	//fua = REQ_OPT_FORCE_UNIT_ACCESS_OFF;
	ReqTransNvmeToSlice(cmdSlotTag, qID, cID, startLba[0], nlb, IO_NVM_READ, fua, NOSTREAM);
	//ReqTransNvmeToSlice(cmdSlotTag, qID, cID, startLba[0], nlb, IO_NVM_READ, 1);
}


void handle_nvme_io_write(unsigned int cmdSlotTag, NVME_IO_COMMAND *nvmeIOCmd, unsigned int qID)
{
	IO_READ_COMMAND_DW12 writeInfo12;
	//IO_READ_COMMAND_DW13 writeInfo13;
	//IO_READ_COMMAND_DW15 writeInfo15;
	unsigned int startLba[2];
	unsigned int nlb, fua, cID;

	writeInfo12.dword = nvmeIOCmd->dword[12];
	//writeInfo13.dword = nvmeIOCmd->dword[13];
	//writeInfo15.dword = nvmeIOCmd->dword[15];

	//if(writeInfo12.FUA == 1)
	//	xil_printf("write FUA\r\n");

	startLba[0] = nvmeIOCmd->dword[10];
	startLba[1] = nvmeIOCmd->dword[11];
	nlb = writeInfo12.NLB;
	fua = writeInfo12.FUA;
	cID = nvmeIOCmd->CID;

	ASSERT(startLba[0] < storageCapacity_L && (startLba[1] < STORAGE_CAPACITY_H || startLba[1] == 0));
	ASSERT(nlb < MAX_NUM_OF_NLB);
	ASSERT((nvmeIOCmd->PRP1[0] & 0xF) == 0 && (nvmeIOCmd->PRP2[0] & 0xF) == 0);
	ASSERT(nvmeIOCmd->PRP1[1] < 0x10000 && nvmeIOCmd->PRP2[1] < 0x10000);

#if (TEST_MODE_FUA == 1)
	fua = REQ_OPT_FORCE_UNIT_ACCESS_ON;
#endif
#if (TEST_MODE_FUA == 2)
	fua = REQ_OPT_FORCE_UNIT_ACCESS_OFF;
#endif

	//fua = REQ_OPT_FORCE_UNIT_ACCESS_OFF;
	ReqTransNvmeToSlice(cmdSlotTag, qID, cID, startLba[0], nlb, IO_NVM_WRITE, fua, NOSTREAM);
}

// (jhpark): TRIM
void hanlde_nvme_io_discard(unsigned int cmdSlotTag, NVME_IO_COMMAND *nvmeIOCmd, unsigned int qID)
{
	IO_DATASET_MANAGEMENT_COMMAND_DW10 dsm10;
	IO_DATASET_MANAGEMENT_COMMAND_DW11 dsm11;

	dsm10.dword = nvmeIOCmd->dword[10];
	dsm11.dword = nvmeIOCmd->dword[11];

	unsigned int nr;
	if (dsm11.AD == 1) {

		nr = dsm10.NR;
		// TODO(jhpark): range 더 추가하기

		unsigned int diff = TEMPORARY_SPARE_DATA_BUFFER_BASE_ADDR % 4096;
		unsigned int new_addr = TEMPORARY_SPARE_DATA_BUFFER_BASE_ADDR + (4096 - diff);

		set_direct_rx_dma((new_addr), nvmeIOCmd->PRP1[1], nvmeIOCmd->PRP1[0], 4096);
		check_direct_rx_dma_done();


		unsigned int len, i;
		unsigned int startLba[2];
		for (i=0; i<nr; i++) {
			DATASET_MANAGEMENT_RANGE* dmr = (DATASET_MANAGEMENT_RANGE*) (new_addr + (sizeof(DATASET_MANAGEMENT_RANGE)*i));
			startLba[0] = dmr->startingLBA[0];
			len = dmr->lengthInLogicalBlocks;
			// (jhpark): real call deallcoate : len is # of lbas
			deallocate(startLba[0], len);
		}

	}
}

void handle_nvme_io_cmd(NVME_COMMAND *nvmeCmd)
{
	NVME_IO_COMMAND *nvmeIOCmd;
	NVME_COMPLETION nvmeCPL;
	unsigned int opc;
	nvmeIOCmd = (NVME_IO_COMMAND*)nvmeCmd->cmdDword;
	/*		xil_printf("OPC = 0x%X\r\n", nvmeIOCmd->OPC);
			xil_printf("PRP1[63:32] = 0x%X, PRP1[31:0] = 0x%X\r\n", nvmeIOCmd->PRP1[1], nvmeIOCmd->PRP1[0]);
			xil_printf("PRP2[63:32] = 0x%X, PRP2[31:0] = 0x%X\r\n", nvmeIOCmd->PRP2[1], nvmeIOCmd->PRP2[0]);
			xil_printf("dword10 = 0x%X\r\n", nvmeIOCmd->dword10);
			xil_printf("dword11 = 0x%X\r\n", nvmeIOCmd->dword11);
			xil_printf("dword12 = 0x%X\r\n", nvmeIOCmd->dword12);*/


	opc = (unsigned int)nvmeIOCmd->OPC;

	switch(opc)
	{
		case IO_NVM_FLUSH:
		{
			//xil_printf("IO Flush Command\r\n");
			nvmeCPL.dword[0] = 0;
			nvmeCPL.specific = 0x0;
			set_auto_nvme_cpl(nvmeCmd->cmdSlotTag, nvmeCPL.specific, nvmeCPL.statusFieldWord);
			break;
		}
		case IO_NVM_WRITE:
		{
			//xil_printf("IO Write Command\r\n");
			handle_nvme_io_write(nvmeCmd->cmdSlotTag, nvmeIOCmd, nvmeCmd->qID);
			break;
		}
		case IO_NVM_READ:
		{
			//xil_printf("IO Read Command\r\n");
			handle_nvme_io_read(nvmeCmd->cmdSlotTag, nvmeIOCmd, nvmeCmd->qID);
			break;
		}
		// (jhpark): TRIM
		case IO_NVM_DATASET_MANAGEMENT:
		{
			// (jhpark): for FIO test, we ignore TRIM command
			/*
			nvmeCPL.dword[0] = 0;
			nvmeCPL.specific = 0x0;
			set_auto_nvme_cpl(nvmeCmd->cmdSlotTag, nvmeCPL.specific, nvmeCPL.statusFieldWord);
			break;
			*/
			// (jhpark): disable TRIM
			//nvmeCPL.dword[0] = 0;
			//nvmeCPL.specific = 0x0;
			//set_auto_nvme_cpl(nvmeCmd->cmdSlotTag, nvmeCPL.specific, nvmeCPL.statusFieldWord);
			//break;
			/*
			if (trim_flag == 0) {
				nvmeCPL.dword[0] = 0;
				nvmeCPL.specific = 0x0;
				set_auto_nvme_cpl(nvmeCmd->cmdSlotTag, nvmeCPL.specific, nvmeCPL.statusFieldWord);
				break;
			}
			*/
			SyncAllLowLevelReqDone();
			hanlde_nvme_io_discard(nvmeCmd->cmdSlotTag, nvmeIOCmd, nvmeCmd->qID);

			nvmeCPL.dword[0] = 0;
			nvmeCPL.specific = 0x0;
			nvmeCPL.statusField.SCT = SCT_GENERIC_COMMAND_STATUS;
			nvmeCPL.statusField.SC = SC_SUCCESSFUL_COMPLETION;
			set_auto_nvme_cpl(nvmeCmd->cmdSlotTag, nvmeCPL.specific, nvmeCPL.statusFieldWord);
			break;
		}
		// (jhpark): PRINT
		case IO_NVM_PRINT_STAT:
		{
			printf("gc: %lld, wr: %lld, hwr: %lld, "
				   "er: %lld, cb: %lld, "
				   "gwr: %lld, gcb: %lld, ggc: %lld trim: %lld\r\n",
				   g_ftl_num_gc, g_ftl_num_write, g_ftl_num_host_write,
				   g_ftl_num_erase, g_ftl_num_copy_back,
				   g_ftl_num_gather_write, g_ftl_num_gather_cp, g_ftl_num_gather_gc, g_ftl_num_trim);
			nvmeCPL.dword[0] = 0;
			nvmeCPL.specific = 0x0;
			set_auto_nvme_cpl(nvmeCmd->cmdSlotTag, nvmeCPL.specific, nvmeCPL.statusFieldWord);
			// (jhpark): activate trim staring on benchmark
			trim_flag = 1;
			break;
		}
		case IO_NVM_STREAM:
		{
			// TODO
			//stream_write(nvmeCmd->cmdSlotTag, nvmeIOCmd, nvmeCmd->qID);
			stream_set(nvmeCmd->cmdSlotTag, nvmeIOCmd, nvmeCmd->qID);

			nvmeCPL.dword[0] = 0;
			nvmeCPL.specific = 0x0;
			nvmeCPL.statusField.SCT = SCT_GENERIC_COMMAND_STATUS;
			nvmeCPL.statusField.SC = SC_SUCCESSFUL_COMPLETION;
			set_auto_nvme_cpl(nvmeCmd->cmdSlotTag, nvmeCPL.specific, nvmeCPL.statusFieldWord);
			break;
		}

		default:
		{
			xil_printf("Not Support IO Command OPC: %X\r\n", opc);
			break;
			//ASSERT(0);
			//break;
		}
	}
}
