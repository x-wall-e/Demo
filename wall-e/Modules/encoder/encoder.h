#ifndef __ENCODER_H
#define __ENCODER_H

#include "stm32f10x.h"
#include "stm32f10x_tim.h"

#define ENCODER_TIM_PERIOD (u16)(65535)   //103的定时器是16位 2的16次方最大是65536
void Encoder_Init_TIM2(void);
void Encoder_Init_TIM4(void);
int Read_Encoder(u8 TIMX);
void TIM4_IRQHandler(void);
void TIM2_IRQHandler(void);

#endif