#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f10x.h"
#include "misc.h"

void delay_init(void);
void delay_ms(u16 nms);
void delay_us(u32 nus);

#endif
