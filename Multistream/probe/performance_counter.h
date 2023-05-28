#ifndef SRC_PROBE_PERFORMANCE_COUNTER_H_
#define SRC_PROBE_PERFORMANCE_COUNTER_H_

#include "xtime_l.h"
#include "../ftl_config.h"

#define PRINT_PERFORMANCE_COUNTER		(0)
#define TIMER_CLKS_PER_OUTPUT_PERIOD_OF_PERFORMANCE_COUNTER	(500000000) //one period is one second
#define INTERVAL_SEC_CHECK_OUTPUT_PERFORMANCE_COUNTER		(60)
#define NANO_SECONDS_PER_TIMER_CLK	(2)

#define NVME_BLOCKS_PER_MB	(1048576 / BYTES_PER_NVME_BLOCK)
#define PAGES_PER_MB	(1048576 / BYTES_PER_DATA_REGION_OF_SLICE)

#define PERFORMANCE_COUNTER_INIT_OPT_ALL	 0
#define PERFORMANCE_COUNTER_INIT_OPT_EXCEPT_IDLE_CHECK_FLAG 1

#define PERFORMANCE_COUNTER_CHANNEL_IDLE_CHECK_END	 0
#define PERFORMANCE_COUNTER_CHANNEL_IDLE_CHECK_START 1

typedef struct _PERFORMANCE_COUNTER_PER_CHANNEL
{
	unsigned int completedNandReadCnt;
	unsigned int completedNandWriteCnt;
	unsigned int completedNandEraseCnt : 16;
	unsigned int idleCheckFlag : 2;
	unsigned int reserved : 14;
	XTime tempClkForIdleCheck;
	XTime idleClkCnt;
} PERFORMANCE_COUNTER_PER_CHANNEL, *P_PERFORMANCE_COUNTER_PER_CHANNEL;


typedef struct _PERFORMANCE_COUNTER_FORMAT
{
	XTime clkofExPeriod;

	unsigned int completedNvmeIoCmdCnt;
	unsigned int completedRxNvmeBlockCnt;
	unsigned int completedTxNvmeBlockCnt;
	unsigned int completedNandReadCnt;
	unsigned int completedNandWriteCnt;
	unsigned int completedNandEraseCnt;//
	unsigned int retryCntForNandRead;//
	unsigned int failCntForNandRead;
	unsigned int failCntForNandWrite;
	unsigned int failCntForNandErase;//
	unsigned int dataBuffForHitCnt;
	unsigned int readModifyWriteCnt;
	unsigned int completedFuaCmdCnt;

	PERFORMANCE_COUNTER_PER_CHANNEL cntPerCh[USER_CHANNELS];
} PERFORMANCE_COUNTER, *P_PERFORMANCE_COUNTER;

void InitPerformanceCounter(unsigned char initOption);
void CheckOutputPeriodOfPerformanceCounter();
void UpdatePerformanceCounterForCompletedNvmeDmaReq(unsigned int reqSlotTag);
void UpdatePerformanceCounterForCompletedNandReq(unsigned int reqSlotTag);
void UpdatePerformanceCounterForCompletedNvmeIoReq();
void UpdatePerformanceCounterForRetriedNandReq(unsigned int reqSlotTag);
void UpdatePerformanceCounterForFailedNandReq(unsigned int reqSlotTag);
void UpdatePerformanceCounterForDataBuffHit();
void UpdatePerformanceCounterForReadModifyWrite();
void UpdatePerformanceCounterForIdleChannel(unsigned int chNo);
void UpdatePerformanceCounterForActiveChannel(unsigned int chNo);
void UpdatePerformanceCounterForCompletedFuaReq(unsigned int reqSlotTag);
void UpdatePerformanceCounterForSettingIdleClkOfEachChannel(XTime endClk);
void AddLogForPerformanceCounter(XTime currentTimerClk);

extern P_PERFORMANCE_COUNTER performanceCounter;

#endif /* SRC_PROBE_PERFORMANCE_COUNTER_H_ */
