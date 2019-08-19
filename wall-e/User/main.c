#include "delay.h"
#include "led.h"
#include "iic.h"
#include "usart.h"
#include "mpu6050.h"
#include <stdio.h>

int main(void)
{
	float f = 1.2;
	int reg = 0;
	LED_Configuration();
	delay_init();
	IIC_Init();
	delay_ms(10);
	MPU6050_Init();
	USART_Configuration();

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
