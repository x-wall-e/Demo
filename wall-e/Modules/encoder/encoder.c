#include "encoder.h"


/********************************************
Function:void Encoder_Init_TIM5(void)
Description: Initialize TIM5 to encoder mode
Input:None
Return:None
Others:None
*********************************************/
void Encoder_Init_TIM5(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_ICInitTypeDef TIM_ICInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);/* Enable Tim5 clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);/* Enable GPIOA clock */

    GPIO_InitStructure.GPIO_Pin = ENCODERA_PIN_1|ENCODERA_PIN_2;  /* Port configuration */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; /* GPIO_Mode_IN_FLOATING */
    GPIO_Init(ENCODERA_PORT, &GPIO_InitStructure);

    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Prescaler = 0x0; /* Prescaler */
    TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD; /* Set counter automatic reload value */
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;/* Select clock division: no division */
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;/* Time Count up mode*/
    TIM_TimeBaseInit(ENCODERA_TIMER, &TIM_TimeBaseStructure);

    TIM_EncoderInterfaceConfig(ENCODERA_TIMER, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);/* Use encoder mode: 3 */

    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 10;
    TIM_ICInit(ENCODERA_TIMER, &TIM_ICInitStructure);
    TIM_ClearFlag(ENCODERA_TIMER, TIM_FLAG_Update);/* Clear the TIM update flag */
    TIM_ITConfig(ENCODERA_TIMER, TIM_IT_Update, ENABLE);

    /* Reset counter */
    TIM_SetCounter(ENCODERA_TIMER,0);
    TIM_Cmd(ENCODERA_TIMER, ENABLE);
}

/********************************************
Function:void Encoder_Init_TIM4(void)
Description: Initialize TIM4 to encoder mode
Input:None
Return:None
Others:None
*********************************************/
void Encoder_Init_TIM4(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_ICInitTypeDef TIM_ICInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);/* Enable Tim4 clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);/* Enable GPIOA clock */

    GPIO_InitStructure.GPIO_Pin = ENCODERB_PIN_1|ENCODERB_PIN_2;	/* Port configuration */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  /* GPIO_Mode_IN_FLOATING */
    GPIO_Init(ENCODERB_PORT, &GPIO_InitStructure);

    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Prescaler = 0x0; /* Prescaler */
    TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD; /* Set counter automatic reload value */
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;/* Select clock division: no division */
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;/* Time Count up mode*/
    TIM_TimeBaseInit(ENCODERB_TIMER, &TIM_TimeBaseStructure);

    TIM_EncoderInterfaceConfig(ENCODERB_TIMER, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);/* Use encoder mode: 3 */

    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 10;
    TIM_ICInit(ENCODERB_TIMER, &TIM_ICInitStructure);
    TIM_ClearFlag(ENCODERB_TIMER, TIM_FLAG_Update);/* Clear the TIM update flag */
    TIM_ITConfig(ENCODERB_TIMER, TIM_IT_Update, ENABLE);

    /* Reset counter */
    TIM_SetCounter(ENCODERB_TIMER,0);
    TIM_Cmd(ENCODERB_TIMER, ENABLE);
}

/********************************************
Function:int Read_Encoder(u8 TIMX)
Description: Read encoder count per unit time
Input:
	u8 TIMX: Timer/Encoder
Return:
	int Encoder_TIM: Speed value
Others:None
*********************************************/
int Read_Encoder(u8 TIMX)
{
    int Encoder_TIM;
    switch(TIMX)
    {
    	case 2:  Encoder_TIM= (short)TIM2 -> CNT;  TIM2 -> CNT=0;break;
    	case 3:  Encoder_TIM= (short)TIM3 -> CNT;  TIM3 -> CNT=0;break;
    	case 4:  Encoder_TIM= (short)TIM4 -> CNT;  TIM4 -> CNT=0;break;
    	default: Encoder_TIM=0;
    }

    return Encoder_TIM;
}

/********************************************
Function:void TIM4_IRQHandler(void)
Description: TIM4 interrupt handle function
Input:None
Return:None
Others:None
*********************************************/
void TIM4IRQHandler(void)
{
    if(TIM4->SR & 0X0001)/* Overflow interrupt */
    {
    }
    TIM4->SR &= ~(1<<0);/* Clear interrupt flag */
}

/********************************************
Function:void TIM2_IRQHandler(void)
Description: TIM2 interrupt handle function
Input:None
Return:None
Others:None
*********************************************/
void TIM5_IRQHandler(void)
{
    if(TIM2->SR & 0X0001)/* Overflow interrupt */
    {
    }
    TIM2->SR &= ~(1<<0);/* Clear interrupt flag */
}
