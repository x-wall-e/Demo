#ifndef __TIMER_H
#define __TIMER_H

#include "data_type.h"

#define INTER_NULL    0u
#define INTER_20MS    1u
#define INTER_100MS       5*INTER_20MS
#define INTER_120MS       6*INTER_20MS
#define INTER_200MS       10*INTER_20MS
#define INTER_240MS       12*INTER_20MS
#define INTER_300MS       15*INTER_20MS
#define INTER_500MS       25*INTER_20MS
#define INTER_600MS       30*INTER_20MS
#define INTER_1000MS      50*INTER_20MS//50*20//50*INTER_20MS
#define INTER_1500MS     75*INTER_20MS
#define INTER_1600MS     80*INTER_20MS
#define INTER_2000MS     100*INTER_20MS
#define INTER_3000MS     150*INTER_20MS
#define INTER_5000MS     250*INTER_20MS
#define INTER_7000MS     350*INTER_20MS
#define INTER_10000MS   500*INTER_20MS
#define INTER_15000MS   725*INTER_20MS
#define INTER_30000MS   1500*INTER_20MS

#pragma pack(1)

typedef struct
{
	uint32 start;
	uint32 interval;
}timer_strcut;

#pragma pack()

extern void timer_set(timer_strcut* t, uint32 interval);
extern uint32 timer_expired( timer_strcut* t);
extern uint32 system_tick;

extern void Delay_Hand(void);
#endif
