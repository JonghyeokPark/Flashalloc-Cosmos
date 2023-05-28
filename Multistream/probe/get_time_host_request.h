/*
 * get_time_host_request.h
 *
 *  Created on: 2021. 6. 11.
 *      Author: SIY
 */

#ifndef SRC_GET_TIME_HOST_REQUEST_H_
#define SRC_GET_TIME_HOST_REQUEST_H_

#include "xtime_l.h"

#define MAX_CMD_SLOT_TAG	1024
#define PRINT_BUFFER_ENTRY_CNT	1024
#define PRINT_BUFFER_DATA_SIZE	256
#define ENTRY_NONE 0xffffffff

typedef struct _HOST_REQUEST_TIME_ENTRY
{
	unsigned int reqCode;
	XTime fetch;
	XTime blockedBufferDef;
	XTime nandReqStart;
	XTime nandReqEnd;
	XTime nvmeDmaStart;
	XTime nvmeDmaEnd;
	unsigned int nvmeDmaCnt;
	unsigned int nandReqCnt;
} HOST_REQUEST_TIME_ENTRY, *P_HOST_REQUEST_TIME_ENTRY;

typedef struct _HOST_REQUEST_TIME_TABLE
{
	HOST_REQUEST_TIME_ENTRY hostRequestTimeEntry[MAX_CMD_SLOT_TAG];
} HOST_REQUEST_TIME_TABLE, *P_HOST_REQUEST_TIME_TABLE;

typedef struct _PRINT_BUFFER_ENTRY
{
	char d[PRINT_BUFFER_DATA_SIZE];
} PRINT_BUFFER_ENTRY, *P_PRINT_BUFFER_ENTRY;

typedef struct _PRINT_BUFFER_TABLE
{
	PRINT_BUFFER_ENTRY buffer[PRINT_BUFFER_ENTRY_CNT];
} PRINT_BUFFER_TABLE, *P_PRINT_BUFFER_TABLE;

void InitHostReqTimeTable();
void AllocateHostReqTime(unsigned int cmdSlotTag, unsigned int reqCode);
void AllocateNvmeDmaCnt(unsigned int cmdSlotTag);
void AllocateNandReqCntForBufferEviction(unsigned int cmdSlotTag);
void GetTimeFetch(unsigned int cmdSlotTag);
void GetTimeBlockedBufferDef(unsigned int cmdSlotTag);
void GetTimeBufferEvictNandReqStart(unsigned int cmdSlotTag, unsigned int reqSlotTag);
void GetTimeBufferEvictNandReqEnd(unsigned int cmdSlotTag, unsigned int reqSlotTag);
void GetTimeHostReqNvmeDmaStart(unsigned int cmdSlotTag);
void GetTimeHostReqNvmeDmaEnd(unsigned int cmdSlotTag);
void ResetHostRequestTimeEntry(unsigned int cmdSlotTag);
void BufferItemValue(unsigned int cmdSlotTag);
void PrintTimeOfHostRequests();

extern P_HOST_REQUEST_TIME_TABLE hostRequestTimeTablePtr;
extern P_PRINT_BUFFER_TABLE printBuffer;
extern unsigned int bufferWritePoint;

#endif /* SRC_GET_TIME_HOST_REQUEST_H_ */
