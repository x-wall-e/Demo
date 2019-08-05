#ifndef __HW_DEBUG_USART_H
#define __HW_DEBUG_USART_H

#include "stm32f10x.h"

#define PIN_USART1_TX  GPIO_Pin_9
#define PIN_USART1_RX  GPIO_Pin_10

#define GPIO_USART1_TX  GPIOA
#define GPIO_USART1_RX  GPIOA

#define USART1_BPS     115200

#define PIN_USART3_TX  GPIO_Pin_10
#define PIN_USART3_RX  GPIO_Pin_11

#define GPIO_USART3_TX GPIOB
#define GPIO_USART3_RX GPIOB

#define USART3_BPS     115200

#define USART_REC_LEN  			(6 * 1024) //定义最大接收字节数 6K

#define EVAL_COM1 USART1

#define SerialPutString(x) Serial_PutString((uint8_t*)(x))

extern void init_debug_usart1_pin_cfg(void);
extern void init_comm_usart3_pin_cfg(void);
extern void Uart1_PutChar(const u8 ch);
extern void Uart1_PutString(const u8 * buf, const u8 len);


#endif

