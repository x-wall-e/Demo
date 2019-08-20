/*
	LED:
		- PC13
	USART1:
		- PA9 - TX
		- PA10 - RX
		- GND
	IMU:
		- SCL - PB6 
		- SDA - PB7
		- VCC - 3.3V
		- GND
	OLED:
		- SCL
		- SDA 
		- VCC
		- GND
	BLUETOOTH: 
		// USART3
		- PB2 - BT_EN
		- PB10 - TX
		- PB11 - RX
		- GND
*/
#include "delay.h"
#include "led.h"
#include "iic.h"
#include "usart1.h"
#include "mpu6050.h"
//#include "usart3.h"
//#include "bluetooth.h"
#include <stdio.h>

/****************************Global Variable*************************************/    
/*Bluetooth remote control related variables*/
int 	Flag_Forward,Flag_Backward,Flag_Left,Flag_Right;	
/********************************************************************************/


/* Hardward Initial */
static void prvSetupHardware(void)
{
	/* LED Configuration */
	LED_Configuration();
	/* Systick Configuration */
	delay_init();
	/* IMU IIC Configuration */
	IIC_Init();
	delay_ms(10);
	/* MPU6050 Configuration */
	MPU6050_Init();
	/* USART1 Configuration */
	Uart1_Init();
	/* USART3 Configuration */
	//Uart3_Init();
	/* Bluetooth Power On */
	//BT_PowerInit();
}

int main(void)
{
	float f = 1.2;
	int reg = 0;

	prvSetupHardware();

	printf("\r\nHello Wall-e.\r\n");
 	while(1)
	{
			//ReadFromIMU();
			f = MPU6050_ReadByte(0x75);
			printf("\r\nreg = %02x\r\n",reg);
			LED_Test();
			//printf("\r\nax: %02f\tay: %02f\taz: %02f\r\n",g_MPU6050Data.accel_x,g_MPU6050Data.accel_y,g_MPU6050Data.accel_z);
			delay_ms(10);
			//printf("\r\ngx: %02f\tgy: %02f\tgz: %02f\r\n",g_MPU6050Data.gyro_x,g_MPU6050Data.gyro_y,g_MPU6050Data.gyro_z);
			delay_ms(100);
	}
}
