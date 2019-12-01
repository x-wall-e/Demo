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

#define ENCODERA_TIMER  TIM2
#define ENCODERA_PORT   GPIOA
#define ENCODERA_PIN_1  GPIO_Pin_1
#define ENCODERA_PIN_2  GPIO_Pin_0

#define ENCODERB_TIMER  TIM4
#define ENCODERB_PORT   GPIOB
#define ENCODERB_PIN_1  GPIO_Pin_6
#define ENCODERB_PIN_2  GPIO_Pin_7

#endif
