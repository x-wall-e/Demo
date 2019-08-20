/*********************************************************************************
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
		- PB10 - TX
		- PB11 - RX
		- GND
		- 5v
	ENCODER:
		// TIM2
		- PA0 - TIM2_CH1_ETR
		- PA1 - TIM2_CH2
		- VCC - 3.3V
		- GND

		// TIM4
		- PB6 - TIM4_CH1
		- PB7 - TIM4_CH2
		- VCC - 3.3V
		- GND
	MOTOR:

*********************************************************************************/

#include "delay.h"
#include "led.h"
#include "iic.h"
#include "usart1.h"
#include "mpu6050.h"
//#include "nvic.h"
//#include "encoder.h"
//#include "usart3.h"
//#include "bluetooth.h"
#include <stdio.h>

/****************************Global Variable*************************************/
/* Bluetooth remote control related variables */
int 	Flag_Forward,Flag_Backward,Flag_Left,Flag_Right;

/*IMUֱ direct sampled data structure */
struct MPU6050_tag g_MPU6050Data;
/********************************************************************************/


/* Hardward Initial */
static void prvSetupHardware(void)
{
	/* LED Configuration */
	LED_Configuration();
	/* Systick Configuration */
	delay_init();
	delay_ms(5000);
	/* IMU IIC Configuration */
	IIC_Init();
	delay_ms(5000);
	/* MPU6050 Configuration */
	MPU6050_Init();
	/* USART1 Configuration */
	Uart1_Init();
	/* USART3 Configuration */
	//Uart3_Init(9600);
	/* NVIC Configuration */
	//NVIC_Configuration();
	/* Bluetooth Power On */
	//BT_PowerInit();
	/* USART3 Re-Configuration */
	//Uart3_Init(115200);
	/* Encoder Configuration*/
	//Encoder_Init_TIM2();
	//Encoder_Init_TIM4();
}

int main(void)
{
	float f = 1.2;
	volatile int reg = 0;
	int encoder2 = 0, encoder4 = 0;

	prvSetupHardware();

	printf("\r\n Hello Wall-e. \r\n");

 	while(1)
	{
			ReadFromIMU();
			reg = MPU6050_ReadByte(WHO_AM_I);
			printf("\r\nreg = %02x\r\n",reg);

			LED_Test();

			/* Find why printf can not use \t */
			//printtf("\r\nax: %02f \tay: %02f \taz: %02f \t",g_MPU6050Data.accel_x,g_MPU6050Data.accel_y,g_MPU6050Data.accel_z);
			printf("\r\nax: %02f \r\nay: %02f \r\naz: %02f \r\n",g_MPU6050Data.accel_x,g_MPU6050Data.accel_y,g_MPU6050Data.accel_z);
			delay_ms(200);
			printf("\r\ngx: %02f \r\ngy: %02f \r\ngz: %02f \r\n",g_MPU6050Data.gyro_x,g_MPU6050Data.gyro_y,g_MPU6050Data.gyro_z);
			delay_ms(200);

			/* Encoder Test */
			//printf("\r\nencoder2 = %d , encoder4 = %d\r\n",-Read_Encoder(2),Read_Encoder(4));
	}
}
