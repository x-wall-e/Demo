#ifndef __ENCODER_H
#define __ENCODER_H

#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include <stdio.h>

/*
	The timer of stm32f103 is 16 bits.
	The maximum of 2^16 is 65536
*/
#define ENCODER_TIM_PERIOD (u16)(65535)

void Encoder_Init_TIM2(void);
void Encoder_Init_TIM4(void);
int Read_Encoder(u8 TIMX);
void TIM4_IRQHandler(void);
void TIM2_IRQHandler(void);

#endif
