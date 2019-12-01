#include "timer.h"
//#include <stdio.h>
#include "SEGGER_RTT.h"
#include "SEGGER_RTT_Conf.h"

//volatile uint16_t anyCnt=0,anyCnt2=0;
//uint8_t  loop500HzFlag,loop200HzFlag,loop50HzFlag,loop600HzFlag,loop100HzFlag,loop20HzFlag,loop10HzFlag;
//volatile uint16_t loop500Hzcnt,loop200HzCnt,loop50HzCnt , loop600HzCnt,loop100HzCnt, loop20HzCnt , loop10HzCnt=0;

/********************************************************************************************************
Function:void TIM4_Int_Init(u16 arr,u16 psc)
Description: Timer4 Init
Input:
	u16 arr: automatic reload value
	u16 psc：clock prescaler
Return:None
Others:
	Tout = (1+TIM_Prescaler ) * (1+TIM_Period ) / Tclk
**********************************************************************************************************/
void TIM4_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	TIM_DeInit(TIM4);

	/*********************************************************+
	| (1 + 71)*(1 + 999) / (72M) Hz = 0.001 s = 1ms //1KHz	  |
	**********************************************************/
	TIM_TimeBaseStructure.TIM_Period = arr; /* The period value to be loaded into the active Auto-Reload Register at the next update event */
	TIM_TimeBaseStructure.TIM_Prescaler = psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	/* Enable or Disable the specific TIM interrupt */
	TIM_ClearFlag(TIM4,TIM_FLAG_Update);
	TIM_ITConfig(
		TIM4,
		TIM_IT_Update ,
		ENABLE
		);

	/* Enable TIMx */
	TIM_Cmd(TIM4, ENABLE);
}
#if 0
/*********************************************************************************************************
Function:void TIM4_IRQHandler(void)
Description: TIM4 IRQHandler
Input:None
Return:None
Others:None
**********************************************************************************************************/
void TIM4_IRQHandler(void)  // 1ms
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
	{
		//TIM_ClearITPendingBit(TIM4 , TIM_FLAG_Update);
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);

		anyCnt++;
		loop200HzCnt++;
		loop100HzCnt++;

		if(++loop50HzCnt * 50 >= 1000)
		{
			printf("\r\nloop50HzCnt\r\n");
			loop50HzCnt=0;
			loop50HzFlag=1;
		}

		if(++loop20HzCnt * 20 >= 1000 )
		{
			printf("\r\nloop20HzCnt\r\n");
			loop20HzCnt=0;
			loop20HzFlag=1;
		}

		if(++loop10HzCnt * 10 >= 1000 )
		{
			printf("\r\nloop10HzCnt\r\n");
			loop10HzCnt=0;
			loop10HzFlag=1;
		}
	}
}
#endif
