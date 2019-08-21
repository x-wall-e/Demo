#ifndef __I2C_H
#define __I2C_H

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x.h"

//-----IIC方向设置-----//
//#define SDA_IN()  {GPIOB->CRH&=0XFFF0FFFF;GPIOB->CRH|=8<<16;}	// 可以修改为输入模式,上下拉均可
//#define SDA_OUT() {GPIOB->CRH&=0XFFF0FFFF;GPIOB->CRH|=3<<16;}	// 可以修改为50MHZ推挽输出，但是用寄存器的方式速度更快
#define SDA_IN()  {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=8<<12;}	// 可以修改为输入模式,上下拉均可
#define SDA_OUT() {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=3<<12;}	// 可以修改为50MHZ推挽输出，但是用寄存器的方式速度更快

//-----IIC操作函数-----//
#define IIC_SCL_H    GPIO_SetBits(GPIOB, GPIO_Pin_10)          // SCL_H
#define IIC_SCL_L    GPIO_ResetBits(GPIOB, GPIO_Pin_10)        // SCL_L
#define IIC_SDA_H    GPIO_SetBits(GPIOB, GPIO_Pin_11)          // SDA_H
#define IIC_SDA_L    GPIO_ResetBits(GPIOB, GPIO_Pin_11)        // SDA_L
#define READ_SDA     GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) // 输入SDA

//-----IIC所有操作函数-----//
void OLED_IIC_Init(void); // 初始化IIC的IO口
void OLED_IIC_Start(void);			    // 发送IIC开始信号
void OLED_IIC_Stop(void);          // 发送IIC停止信号
void OLED_IIC_Send_Byte(u8 txd);		// IIC发送一个字节
u8 OLED_IIC_Read_Byte(u8 ack);	    // IIC读取一个字节
u8 OLED_IIC_Wait_Ack(void);        // IIC等待ACK信号
void OLED_IIC_Ack(void);           // IIC发送ACK信号
void OLED_IIC_NAck(void);          // IIC不发送ACK信号

#endif