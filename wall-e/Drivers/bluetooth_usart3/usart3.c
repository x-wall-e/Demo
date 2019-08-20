#include "usart3.h"

/******************************************************************************************
Function:void uart3_init(u32 bound)
Description:Initial uart3
Input:None
Return:None
Others:
	Bluetooth module default communication baud rate is 9600.
		1.Uart3 is initialized to the baud rate (9600) that can communicate with Bluetooth. 
		2.Set bluetooth module baud rate:115200.
		3.Re-initialize uart3 to the baud rate 115200.
*******************************************************************************************/
void Uart3_Init(u32 bound)
{  	 
	//GPIO Configuration
  	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//Enable GPIOB clock
  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//Enable USART3 clock
	
	//USART3_TX  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB.10
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	// GPIO_Mode_AF_PP
	GPIO_Init(GPIOB, &GPIO_InitStructure);
   
	//USART3_RX	  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PB11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;// GPIO_Mode_IN_FLOATING
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//USART Configuration
	USART_InitStructure.USART_BaudRate = bound;// 
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//Word length: 8-bit 
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//StopBits: 1-bit
	USART_InitStructure.USART_Parity = USART_Parity_No;//No parity
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//No hardware data flow control
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//RX + TX mode
	USART_Init(USART3, &USART_InitStructure);     //Initial usart3
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//Enable serial port receive interrupt
	USART_Cmd(USART3, ENABLE);                    //Enable usart3
}

/*************************************
Function:void USART3_IRQHandler(void)
Description:USART3_IRQHandler
Input:None
Return:None
Others:None
*************************************/
void USART3_IRQHandler(void)
{	
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) //Received data
	{	 
		#if 0
		static	int uart_receive=0;//Bluetooth receiving variables
		uart_receive=USART_ReceiveData(USART3); 
		if(uart_receive==0x00)	Flag_Qian=0,Flag_Hou=0,Flag_Left=0,Flag_Right=0;//////////////brake
		else if(uart_receive==0x01)	Flag_Qian=1,Flag_Hou=0,Flag_Left=0,Flag_Right=0;//////////////forward
		else if(uart_receive==0x05)	Flag_Qian=0,Flag_Hou=1,Flag_Left=0,Flag_Right=0;//////////////backward
		else if(uart_receive==0x02||uart_receive==0x03||uart_receive==0x04)	
													Flag_Qian=0,Flag_Hou=0,Flag_Left=0,Flag_Right=1;  //left
		else if(uart_receive==0x06||uart_receive==0x07||uart_receive==0x08)	    //right
													Flag_Qian=0,Flag_Hou=0,Flag_Left=1,Flag_Right=0;
		else Flag_Qian=0,Flag_Hou=0,Flag_Left=0,Flag_Right=0;		//////////////forward
		#endif
	}  											 
} 

/********************************************
Function:void Uart3SendByte(char byte)
Description:Serial port sends a byte
Input:
	char byte: The byte that need to be sent
Return:None
Others:None
*********************************************/
void Uart3SendByte(char byte)   
{
        USART_SendData(USART3, byte);//Send data through library function
        while( USART_GetFlagStatus(USART3,USART_FLAG_TC)!= SET);  
        //Wait for the send to complete. Check if USART_FLAG_TC is set to 1; // see library function P359
 }

/*****************************************************
Function:void Uart3SendBuf(char *buf, u16 len)
Description:Serial port sends a buffer
Input:
	char *buf: The start address of buffer
	u16 len: The number of bytes that need to be sent
Return:None
Others:None
*****************************************************/
void Uart3SendBuf(char *buf, u16 len)
{
	u16 i;
	for(i=0; i<len; i++)Uart3SendByte(*buf++);
}

/*********************************************
Function:void Uart3SendStr(char *str)
Description:Serial port sends a string
Input:
	char *str: The start address of the string
Return:None
Others:None
**********************************************/
void Uart3SendStr(char *str)
{
	u16 i,len;
	len = strlen(str);
	for(i=0; i<len; i++)Uart3SendByte(*str++);
}


