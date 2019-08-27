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
		- SCL - PB10
		- SDA - PB11
		- VCC - 3.3V
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
		- PA6 - TIM3_CH1
		- PA7 - TIM3_CH2
		- VCC - 3.3V
		- GND
	MOTOR:
		- VCC - 5V
		- GND

		//MOTOR-A		
		- AIN1 - PB14
		- AIN2 - PB15
		- PWMA - PA8(TIM1-CH1)
		- GND - GND

		//MOTOR-B
		- BIN1 - PB13
		- BIN2 - PB12
		- PWMB - PA11(TIM1-CH4)
		- GND - GND
*********************************************************************************/

#include "delay.h"
#include "timer.h"
#include "led.h"
#include "iic.h"
#include "usart1.h"
#include "mpu6050.h"
#include "nvic.h"
#include "encoder.h"
#include "control.h"
//#include "usart3.h"
//#include "bluetooth.h"
//#include "pwm.h"
//#include "oled.h"
#include <stdio.h>

/**********************************Global Variable***********************************************************/
/* Bluetooth remote control related variables */
int 	Flag_Forward,Flag_Backward,Flag_Left,Flag_Right;

/*IMUֱ direct sampled data structure */
struct MPU6050_tag g_MPU6050Data;

float pitch = 0.0,roll = 0.0,yaw = 0.0;

/* Control frequency */
extern volatile uint16_t anyCnt,anyCnt2;
extern uint8_t  loop500HzFlag,loop200HzFlag,loop50HzFlag,loop600HzFlag,loop100HzFlag,loop20HzFlag,loop10HzFlag;
/*************************************************************************************************************/

/* Hardward Initial */
static void prvSetupHardware(void)
{
	/* SystemClock Configuration, Clock source uses external crystal oscillator(HSEs), 8*9 = 72MHz */
	SystemClock_HSE(9);           
	/* LED Configuration */
	LED_Configuration();
	/* Systick Configuration */
	delay_init();
	delay_ms(2000);
	/* Timer3 Configuration */
	//TIM3_Int_Init(SysClock,1000);
	/* IMU IIC Configuration */
	MPU6050_IIC_Init();
	/* MPU6050 Configuration */
	MPU6050_Init();
	/* MPU6050 DMP Configuration */
	mpu_dmp_init();	
	/* USART1 Configuration */
	Uart1_Init();
	/* USART3 Configuration */
	//Uart3_Init(9600);
	/* NVIC Configuration */
	NVIC_Configuration();
	/* Bluetooth Power On */
	//BT_PowerInit();
	/* USART3 Re-Configuration */
	//Uart3_Init(115200);
	/* Encoder Configuration*/
	Encoder_Init_TIM2();
	Encoder_Init_TIM3();
	/* Init PWM 10KHZ for motor */
	//TIM1_PWM_Init(7199,0);
	//delay_ms(1000);
	//delay_ms(1000);
	/* Motor io Configuration */
	//Motor_Init();	
	/* OLED IIC Configuration */
	//OLED_IIC_Init();
	/* MPU6050 Configuration */
	//OLED_Init();
	//OLED_Clear();
	//LED_ShowString(0,4,"DAYUTC OLED Test",12);
}

int main(void)
{
	float f = 1.2;
	s16 temp;
	volatile int reg = 0;
	int encoder2 = 0, encoder3 = 0;

	prvSetupHardware();

	printf("\r\n Hello Wall-e. \r\n");

 	while(1)
	{
		LED_Test();
		
		//100Hz Loop
        if(loop100HzCnt>=10)
        {
            loop100HzCnt=0;
			//mpu_dmp_get_data(&pitch, &roll, &yaw);//得到欧拉角（姿态角）的数据
			//ReadFromIMU();
			//Encoder_Left=-Read_Encoder(2);
			//Encoder_Right=Read_Encoder(4); 
			//Balance_Pwm =balance_UP(pitch,Mechanical_angle,gyroy);   //平衡环PID控制
			//Velocity_Pwm=velocity(Encoder_Left,Encoder_Right);       //速度环PID控制	
			//Moto1=Balance_Pwm-Velocity_Pwm-Turn_Pwm;                 //计算左轮电机最终PWM
			//Moto2=Balance_Pwm-Velocity_Pwm+Turn_Pwm;                 //计算右轮电机最终PWM
			//Xianfu_Pwm();  										   //PWM限幅
			//Turn_Off(pitch);								   		   //检查角度以及电压是否正常
			//Set_Pwm(Moto1,Moto2);                                    //赋值给PWM寄存器  			
        }
		
		/* DMP Test */
		//mpu_dmp_get_data(&pitch, &roll, &yaw);
		//printf("\r\n pitch = %f, roll = %f, yaw = %f\r\n",pitch, roll, yaw);
		/* IMU Test */
		//MPU6050_Check();
		//ReadFromIMU();
		//temp = MPU_Get_Temperature();
		//printf("\r\n temp = %d\r\n",temp);
		/* Find why printf can not use \t */
		//printtf("\r\nax: %02f \tay: %02f \taz: %02f \t",g_MPU6050Data.accel_x,g_MPU6050Data.accel_y,g_MPU6050Data.accel_z);
		//printf("\r\nax: %d \r\nay: %d \r\naz: %d \r\n",g_MPU6050Data.accel_x,g_MPU6050Data.accel_y,g_MPU6050Data.accel_z);
		//delay_ms(200);
		//printf("\r\ngx: %d \r\ngy: %d \r\ngz: %d \r\n",g_MPU6050Data.gyro_x,g_MPU6050Data.gyro_y,g_MPU6050Data.gyro_z);

		/* Encoder Test */
		//printf("\r\nencoder2 = %d , encoder4 = %d\r\n",Read_Encoder(2),Read_Encoder(3));
	}
}
