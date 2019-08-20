#include "nvic.h"
   
/********************************************************************************************************
Function:void NVIC_Configuration(void)
Description:NVIC Configuration
Input:None
Return:None
Others:
	NVIC_Channel           : Interrupt entrance
	NVIC_PreemptionPriority: Preemption priority
	NVIC_SubPriority       : Response priority
	NVIC_Group             : Interrupt group 0~4
	
	Group division:
		Group 0: 0-bit preemption priority,4-bit response priority
		Group 1: 1-bit preemption priority,3-bit response priority
		Group 2: 2-bit preemption priority,2-bit response priority
		Group 3: 3-bit preemption priority,1-bit response priority
		Group 4: 4-bit preemption priority,0-bit response priority
	
	Note:
		1.The priority cannot exceed the range of the set group,Otherwise there will be unexpected errors.
		2.NVIC_SubPriority/NVIC_PreemptionPriority: the smaller the value, the higher the priority.
**********************************************************************************************************/
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef  NVIC_InitStructure;	
	/* Use NVIC interrupt Group 2: 2-bit preemption priority, 2-bit response priority */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	

	//////////////////定时器3的中断优先级配置//////////////////		
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;  //先占优先级1级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	/* Usart3 NVIC interrupt priority configuration (Bluetooth serial port configuration) */
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x02 ;/* Preemption priority: 2 */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;	   /* Response priority: 2 */
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			   /* IRQ channel enable */
	/* Initialize the peripheral NVIC register according to the parameters specified in NVIC_InitStruct	*/
	NVIC_Init(&NVIC_InitStructure);	
}