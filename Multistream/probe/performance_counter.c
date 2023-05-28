#include "performance_counter.h"
#include "../request_allocation.h"
#include "../address_translation.h"
#include "../memory_map.h"

P_PERFORMANCE_COUNTER performanceCounter;

void InitPerformanceCounter(unsigned char initOption)
{
	unsigned int tempCh;
	performanceCounter = (P_PERFORMANCE_COUNTER)PERFORMANCE_COUNTER_ADDR;

	XTime_GetTime(&(performanceCounter->clkofExPeriod));

	performanceCounter->completedNvmeIoCmdCnt = 0;
	performanceCounter->completedRxNvmeBlockCnt = 0;
	performanceCounter->completedTxNvmeBlockCnt = 0;
	performanceCounter->completedNandReadCnt = 0;
	performanceCounter->completedNandWriteCnt = 0;
	performanceCounter->completedNandEraseCnt = 0;
	performanceCounter->retryCntForNandRead = 0;
	performanceCounter->failCntForNandRead = 0;
	performanceCounter->failCntForNandWrite = 0;
	performanceCounter->failCntForNandErase = 0;
	performanceCounter->dataBuffForHitCnt = 0;
	performanceCounter->readModifyWriteCnt = 0;
	performanceCounter->completedFuaCmdCnt = 0;

	for(tempCh = 0; tempCh < USER_CHANNELS; tempCh++)
	{
		performanceCounter->cntPerCh[tempCh].completedNandReadCnt = 0;
		performanceCounter->cntPerCh[tempCh].completedNandWriteCnt = 0;
		performanceCounter->cntPerCh[tempCh].completedNandEraseCnt = 0;
		if(initOption != PERFORMANCE_COUNTER_INIT_OPT_EXCEPT_IDLE_CHECK_FLAG)
			performanceCounter->cntPerCh[tempCh].idleCheckFlag = PERFORMANCE_COUNTER_CHANNEL_IDLE_CHECK_START;
		performanceCounter->cntPerCh[tempCh].tempClkForIdleCheck = performanceCounter->clkofExPeriod;
		performanceCounter->cntPerCh[tempCh].idleClkCnt = 0;
	}
}


void CheckOutputPeriodOfPerformanceCounter()
{
	XTime tempClk;

	XTime_GetTime(&tempClk);

	if((tempClk-performanceCounter->clkofExPeriod)/(TIMER_CLKS_PER_OUTPUT_PERIOD_OF_PERFORMANCE_COUNTER) > INTERVAL_SEC_CHECK_OUTPUT_PERFORMANCE_COUNTER)
	{
		UpdatePerformanceCounterForSettingIdleClkOfEachChannel(tempClk);
#if (PRINT_PERFORMANCE_COUNTER == 1)
		AddLogForPerformanceCounter(tempClk);
#endif
		InitPerformanceCounter(PERFORMANCE_COUNTER_INIT_OPT_EXCEPT_IDLE_CHECK_FLAG);
	}
}

void UpdatePerformanceCounterForCompletedNvmeDmaReq(unsigned int reqSlotTag)
{
	if(reqPoolPtr->reqPool[reqSlotTag].reqCode == REQ_CODE_RxDMA)
	{
		performanceCounter->completedRxNvmeBlockCnt += reqPoolPtr->reqPool[reqSlotTag].nvmeDmaInfo.numOfNvmeBlock;
	}
	else if(reqPoolPtr->reqPool[reqSlotTag].reqCode == REQ_CODE_TxDMA)
	{
		performanceCounter->completedTxNvmeBlockCnt += reqPoolPtr->reqPool[reqSlotTag].nvmeDmaInfo.numOfNvmeBlock;
	}
}

void UpdatePerformanceCounterForCompletedNandReq(unsigned int reqSlotTag)
{
	unsigned int chNo;

	chNo = Vdie2PchTranslation(Vsa2VdieTranslation(reqPoolPtr->reqPool[reqSlotTag].nandInfo.virtualSliceAddr));

	if((reqPoolPtr->reqPool[reqSlotTag].reqCode == REQ_CODE_READ_TRANSFER) ||((reqPoolPtr->reqPool[reqSlotTag].reqCode == REQ_CODE_READ)))
	{
		performanceCounter->completedNandReadCnt++;
		performanceCounter->cntPerCh[chNo].completedNandReadCnt++;

	}
	else if(reqPoolPtr->reqPool[reqSlotTag].reqCode == REQ_CODE_WRITE)
	{
		performanceCounter->completedNandWriteCnt++;
		performanceCounter->cntPerCh[chNo].completedNandWriteCnt++;
	}
	else if(reqPoolPtr->reqPool[reqSlotTag].reqCode == REQ_CODE_ERASE)
	{
		performanceCounter->completedNandEraseCnt++;
		performanceCounter->cntPerCh[chNo].completedNandEraseCnt++;
	}
}

void UpdatePerformanceCounterForCompletedNvmeIoReq()
{
	performanceCounter->completedNvmeIoCmdCnt++;
}

void UpdatePerformanceCounterForRetriedNandReq(unsigned int reqSlotTag)
{
	if((reqPoolPtr->reqPool[reqSlotTag].reqCode == REQ_CODE_READ_TRANSFER) ||((reqPoolPtr->reqPool[reqSlotTag].reqCode == REQ_CODE_READ)))
	{
		performanceCounter->retryCntForNandRead++;
	}
}

void UpdatePerformanceCounterForFailedNandReq(unsigned int reqSlotTag)
{
	if((reqPoolPtr->reqPool[reqSlotTag].reqCode == REQ_CODE_READ_TRANSFER) ||((reqPoolPtr->reqPool[reqSlotTag].reqCode == REQ_CODE_READ)))
	{
		performanceCounter->failCntForNandRead++;
	}
	else if(reqPoolPtr->reqPool[reqSlotTag].reqCode == REQ_CODE_WRITE)
	{
		performanceCounter->failCntForNandWrite++;
	}
	else if(reqPoolPtr->reqPool[reqSlotTag].reqCode == REQ_CODE_ERASE)
	{
		performanceCounter->failCntForNandErase++;
	}
}

void UpdatePerformanceCounterForDataBuffHit()
{
	performanceCounter->dataBuffForHitCnt++;
}

void UpdatePerformanceCounterForReadModifyWrite()
{
	performanceCounter->readModifyWriteCnt++;
}

void UpdatePerformanceCounterForIdleChannel(unsigned int chNo)
{
	if(performanceCounter->cntPerCh[chNo].idleCheckFlag == PERFORMANCE_COUNTER_CHANNEL_IDLE_CHECK_END)
	{
		XTime_GetTime(&performanceCounter->cntPerCh[chNo].tempClkForIdleCheck);
		performanceCounter->cntPerCh[chNo].idleCheckFlag = PERFORMANCE_COUNTER_CHANNEL_IDLE_CHECK_START;
	}
}


void UpdatePerformanceCounterForActiveChannel(unsigned int chNo)
{
	if(performanceCounter->cntPerCh[chNo].idleCheckFlag == PERFORMANCE_COUNTER_CHANNEL_IDLE_CHECK_START)
	{
		XTime idleEndClk;
		XTime_GetTime(&idleEndClk);

		performanceCounter->cntPerCh[chNo].idleClkCnt += (idleEndClk - performanceCounter->cntPerCh[chNo].tempClkForIdleCheck);
		performanceCounter->cntPerCh[chNo].idleCheckFlag = PERFORMANCE_COUNTER_CHANNEL_IDLE_CHECK_END;
	}
}

void UpdatePerformanceCounterForCompletedFuaReq(unsigned int reqSlotTag)
{
	if(reqPoolPtr->reqPool[reqSlotTag].reqOpt.forceUnitAccess == REQ_OPT_FORCE_UNIT_ACCESS_ON)
		performanceCounter->completedFuaCmdCnt++;
}

void UpdatePerformanceCounterForSettingIdleClkOfEachChannel(XTime endClk)
{
	unsigned int chNo;

	for (chNo = 0; chNo < USER_CHANNELS; chNo++)
	{
		if (performanceCounter->cntPerCh[chNo].idleCheckFlag == PERFORMANCE_COUNTER_CHANNEL_IDLE_CHECK_START)
			performanceCounter->cntPerCh[chNo].idleClkCnt += (endClk - performanceCounter->cntPerCh[chNo].tempClkForIdleCheck);
	}
}


void AddLogForPerformanceCounter(XTime currentTimerClk)
{
	XTime timeStamp;
	unsigned int nanoSecondsOfThisPeriod;

	unsigned int ioPerSecForSsd;
	unsigned int megaBytesPerSecForSsdRead;
	unsigned int megaBytesPerSecForSsdWrite;
	unsigned int megaBytesPerSecForNandRead;
	unsigned int megaBytesPerSecForNandWrite;

	unsigned int erasedBlockCnt;
	unsigned int retryCntForNandRead;
	unsigned int failCntForNandRead;
	unsigned int failCntForNandWrite;
	unsigned int failCntForNandErase;

	unsigned int dataBuffForHitCnt;
	unsigned int readModifyWriteCnt;
	unsigned int fuaCnt;

	XTime timerClksForThisPeriod = currentTimerClk - performanceCounter->clkofExPeriod;
	double secondsOfThisPeriod = (double)timerClksForThisPeriod / ((double)(TIMER_CLKS_PER_OUTPUT_PERIOD_OF_PERFORMANCE_COUNTER)*(double)(INTERVAL_SEC_CHECK_OUTPUT_PERFORMANCE_COUNTER));
	double nvmeBlocksPerMegaByte = NVME_BLOCKS_PER_MB;
	double pagesPerMegaByte = PAGES_PER_MB;

	timeStamp = currentTimerClk * NANO_SECONDS_PER_TIMER_CLK;
	nanoSecondsOfThisPeriod = timerClksForThisPeriod * NANO_SECONDS_PER_TIMER_CLK;
	ioPerSecForSsd = (double)performanceCounter->completedNvmeIoCmdCnt / secondsOfThisPeriod;
	megaBytesPerSecForSsdRead = ((double)performanceCounter->completedTxNvmeBlockCnt / nvmeBlocksPerMegaByte) / secondsOfThisPeriod;
	megaBytesPerSecForSsdWrite = ((double)performanceCounter->completedRxNvmeBlockCnt / nvmeBlocksPerMegaByte) / secondsOfThisPeriod;
	megaBytesPerSecForNandRead = ((double)performanceCounter->completedNandReadCnt / pagesPerMegaByte) / secondsOfThisPeriod;
	megaBytesPerSecForNandWrite = ((double)performanceCounter->completedNandWriteCnt / pagesPerMegaByte) / secondsOfThisPeriod;
	erasedBlockCnt = performanceCounter->completedNandEraseCnt;
	retryCntForNandRead = performanceCounter->retryCntForNandRead;
	failCntForNandRead = performanceCounter->failCntForNandRead;
	failCntForNandWrite = performanceCounter->failCntForNandWrite;
	failCntForNandErase = performanceCounter->failCntForNandErase;
	dataBuffForHitCnt = performanceCounter->dataBuffForHitCnt;
	readModifyWriteCnt = performanceCounter->readModifyWriteCnt;
	fuaCnt = performanceCounter->completedFuaCmdCnt;

	xil_printf("SsdRead %dMB SsdWrite %dMB NandRead %dMB NandWrite %dMB FUA %d EraseCnt %d RMW %d\r\n",
			megaBytesPerSecForSsdRead, megaBytesPerSecForSsdWrite, megaBytesPerSecForNandRead, megaBytesPerSecForNandWrite, fuaCnt, erasedBlockCnt, readModifyWriteCnt);
}



