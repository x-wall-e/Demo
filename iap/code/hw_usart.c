#include "hw_usart.h"

//u16 USART_RX_STA=0;       //接收状态标记	
//u16 USART_RX_CNT=0;				//接收的字节数	
//u8 USART_RX_BUF[USART_REC_LEN] __attribute__ ((at(0X20001000)));//接收缓冲,最大USART_REC_LEN个字节,起始地址为0X20001000. 

void usart1_pin_init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOA,ENABLE);
	
    GPIO_InitStructure.GPIO_Pin = PIN_USART1_TX;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIO_USART1_TX, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = PIN_USART1_RX;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   
    GPIO_Init(GPIO_USART1_RX, &GPIO_InitStructure);

}

void usart1_configuration(void)
{
    USART_InitTypeDef USART_InitStructure;
    USART_ClockInitTypeDef  USART_ClockInitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);

    USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
    USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;
    USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
    USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;
    USART_ClockInit(USART1, &USART_ClockInitStructure);

    USART_InitStructure.USART_BaudRate = USART1_BPS;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
    //USART_InitStructure.USART_Mode = USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);
	//USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

}

void usart1_nvic_configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void init_debug_usart1_pin_cfg(void)
{
  usart1_configuration();
	usart1_pin_init();
	
	//usart1_nvic_configuration();
}

void usart3_pin_init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
    GPIO_InitStructure.GPIO_Pin = PIN_USART3_TX;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIO_USART3_TX, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = PIN_USART3_RX;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   
    GPIO_Init(GPIO_USART3_RX, &GPIO_InitStructure);

}

void usart3_configuration(void)
{
    USART_InitTypeDef USART_InitStructure;
    USART_ClockInitTypeDef  USART_ClockInitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);

    USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
    USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;
    USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
    USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;
    USART_ClockInit(USART3, &USART_ClockInitStructure);

    USART_InitStructure.USART_BaudRate = USART3_BPS;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
    USART_Init(USART3, &USART_InitStructure);
    USART_Cmd(USART3, ENABLE);
		USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

}

void init_comm_usart3_pin_cfg(void)
{
	usart3_pin_init();
	usart3_configuration();
}

void Uart1_PutChar(const u8 ch)
{
   USART_SendData(USART1, (u8)ch);
   while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
   //while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
}


void Uart1_PutString(const u8 * buf, const u8 len)
{   
	u8 i;
	
	for(i = 0; i < len; i++)
		Uart1_PutChar(*buf++);
}



