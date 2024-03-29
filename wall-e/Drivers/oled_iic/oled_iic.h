#ifndef __OLED_IIC_H
#define __OLED_IIC_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "delay.h"

//-----IIC Direction setting-----//
#define SDA_IN()  {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=8<<12;}	// Can be modified to input mode, both up and down input mode
#define SDA_OUT() {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=3<<12;}	// Can be modified to 50MHZ push-pull output, but faster with registers

/* Remap */
#define OLED_SDA_PORT   GPIOB
#define OLED_SDA_PIN    GPIO_Pin_9
#define OLED_SCL_PORT   GPIOB
#define OLED_SDA_PIN    GPIO_Pin_8

//-----IIC Operation Func-----//
#define IIC_SCL_H    GPIO_SetBits(GPIOB, GPIO_Pin_10)          // SCL_H
#define IIC_SCL_L    GPIO_ResetBits(GPIOB, GPIO_Pin_10)        // SCL_L
#define IIC_SDA_H    GPIO_SetBits(GPIOB, GPIO_Pin_11)          // SDA_H
#define IIC_SDA_L    GPIO_ResetBits(GPIOB, GPIO_Pin_11)        // SDA_L
#define READ_SDA     GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) // Input SDA


void OLED_IIC_Init(void); // iic initialization
void OLED_IIC_Start(void);			    //Generate iic start signal
void OLED_IIC_Stop(void);          //Generate iic stop signal
void OLED_IIC_Send_Byte(u8 txd);		//iic send a byte
u8 OLED_IIC_Read_Byte(u8 ack);	    //iic read a byte
u8 OLED_IIC_Wait_Ack(void);        //Waiting for the response signal to arrive
void OLED_IIC_Ack(void);           //Generate Ack response
void OLED_IIC_NAck(void);          //Generate NAck response

#endif
