#ifndef __IIC_H
#define __IIC_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "delay.h"

//-----IIC Direction setting-----//
#define SDA_IN()  {GPIOB->CRH&=0XFFF0FFFF;GPIOB->CRH|=8<<16;}	// Can be modified to input mode, both up and down input mode
#define SDA_OUT() {GPIOB->CRH&=0XFFF0FFFF;GPIOB->CRH|=3<<16;}	// Can be modified to 50MHZ push-pull output, but faster with registers

//-----IIC Operation Func-----// 
#define IIC_SCL_H    GPIO_SetBits(GPIOB, GPIO_Pin_6) // SCL_H
#define IIC_SCL_L    GPIO_ResetBits(GPIOB, GPIO_Pin_6)// SCL_L
#define IIC_SDA_H    GPIO_SetBits(GPIOB, GPIO_Pin_7) // SDA_H
#define IIC_SDA_L    GPIO_ResetBits(GPIOB, GPIO_Pin_7) // SDA_L 
#define READ_SDA    GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7)  // Input SDA


void IIC_Init(void);			//iic initialization
void IIC_Start(void);			//Generate iic start signal
void IIC_Stop(void);	  		//Generate iic stop signal
void IIC_Send_Byte(u8 txd);		//iic send a byte
u8 IIC_Read_Byte(u8 ack);		//iic read a byte
u8 IIC_Wait_Ack(void); 			//Waiting for the response signal to arrive
void IIC_Ack(void);				//Generate Ack response
void IIC_NAck(void);			//Generate NAck response

#endif
