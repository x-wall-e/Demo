#include "pwm.h"

/********************************************
Function：void TIM1_PWM_Init(u16 arr,u16 psc)
Description: PWM output initialization
Input:
	u16 arr: automatic reload value
	u16 psc：clock prescaler
Return:None
Others:
	TIM1_PWM_Init(7199,0);
		- PWM frequency:
			72000Mhz / (7199+1) = 10Khz
*********************************************/
void TIM1_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);/* Enable Tim1 clock */
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);/* Enable GPIOA clock */
	
	/*
		- Set GPIOA.8 and GPIOA.11 as the GPIO_Mode_AF_PP function.
		- Output the PWM pulse waveform of TIM1-CH1 and TIM1-CH4.
		- GPIOA.8  - TIM1-CH1.
		- GPIOA.11 - TIM1-CH4
	*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  /* GPIO_Mode_AF_PP */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	TIM_TimeBaseStructure.TIM_Period = arr; /* The period value to be loaded into the active Auto-Reload Register at the next update event */ 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; /*The prescaler value used to divide the TIM clock: 0 - No frequency division */
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; /* Set clock division: TDTS = Tck_tim */
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; /* Count up mode */
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; /*Select timer mode: TIM PWM mode 1*/
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; /* Compare output enable */
	TIM_OCInitStructure.TIM_Pulse = 0; /* The pulse value to be loaded into the Capture Compare Register */
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; /* The output polarity */
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);  
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);  

	TIM_CtrlPWMOutputs(TIM1,ENABLE); /* MOE: main output enable */

	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  /* CH1 Preload enable */ 
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  /* CH4 Preload enable */	 
	
	TIM_ARRPreloadConfig(TIM1, ENABLE); /* Enable TIMx preload register on ARR */
	
	TIM_Cmd(TIM1, ENABLE); /* Enable TIM1 */
}