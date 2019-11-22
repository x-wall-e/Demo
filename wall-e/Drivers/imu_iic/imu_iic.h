#ifndef __IMU_IIC_H
#define __IMU_IIC_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "delay.h"

//-----IIC Direction setting-----//
#define SDA_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=8<<12;}	// Can be modified to input mode, both up and down input mode
#define SDA_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=3<<12;}	// Can be modified to 50MHZ push-pull output, but faster with registers

#define IMU_SDA_PORT    GPIOB
#define IMU_SDA_PIN     GPIO_Pin_3
#define IMU_SCL_PORT    GPIOB
#define IMU_SCL_PIN     GPIO_Pin_4

//-----IIC Operation Func-----//
#define IIC_SCL_H    GPIO_SetBits(IMU_SCL_PORT, IMU_SCL_PIN) // SCL_H
#define IIC_SCL_L    GPIO_ResetBits(IMU_SCL_PORT, IMU_SCL_PIN)// SCL_L
#define IIC_SDA_H    GPIO_SetBits(IMU_SDA_PORT, IMU_SDA_PIN) // SDA_H
#define IIC_SDA_L    GPIO_ResetBits(IMU_SDA_PORT, IMU_SDA_PIN) // SDA_L
#define READ_SDA     GPIO_ReadInputDataBit(IMU_SDA_PORT, IMU_SDA_PIN)  // Input SDA


void MPU6050_IIC_Init(void);        //iic initialization
void IIC_Start(void);               //Generate iic start signal
void IIC_Stop(void);                //Generate iic stop signal
void IIC_Send_Byte(u8 txd);         //iic send a byte
u8 IIC_Read_Byte(u8 ack);           //iic read a byte
u8 IIC_Wait_Ack(void);              //Waiting for the response signal to arrive
void IIC_Ack(void);                 //Generate Ack response
void IIC_NAck(void);                //Generate NAck response

#endif
