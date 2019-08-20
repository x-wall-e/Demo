#ifndef __USRAT3_H
#define __USRAT3_H

#include "stm32f10x.h"
#include "stm32f10x_usart.h"

extern u8 Usart3_Receive;
extern int 	Flag_Forward,Flag_Backward,Flag_Left,Flag_Right;

void Uart3_Init(u32 bound);
void USART3_IRQHandler(void);
void Uart3SendByte(char byte);
void Uart3SendBuf(char *buf, u16 len);
void Uart3SendStr(char *str);
#endif
