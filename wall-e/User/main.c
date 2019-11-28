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
#include "usart1.h"
#include "mpu6050.h"
#include "nvic.h"
#include "encoder.h"
#include "control.h"
#include "inv_mpu.h"
#include "motor.h"
//#include "usart3.h"
#include "bluetooth.h"
#include "pwm.h"
#include "sys.h"
//#include "oled.h"
//#include <stdio.h>
#include "SEGGER_RTT.h"
#include "SEGGER_RTT_Conf.h"

/**********************************Global Variable***********************************************************/
/* Bluetooth remote control related variables */
int 	Flag_Forward,Flag_Backward,Flag_Left,Flag_Right;

/*IMUֱ direct sampled data structure */
//struct MPU6050_tag g_MPU6050Data;

volatile float pitch = 0.0,roll = 0.0,yaw = 0.0;

int     Moto1=0,Moto2=0;

u8    flag_fall=0;

int   Encoder_Left,Encoder_Right;

/* Control frequency */
extern volatile uint16_t anyCnt,anyCnt2;
extern uint8_t  loop500HzFlag,loop200HzFlag,loop50HzFlag,loop600HzFlag,loop100HzFlag,loop20HzFlag,loop10HzFlag;
extern volatile uint16_t loop500Hzcnt,loop200HzCnt,loop50HzCnt , loop600HzCnt,loop100HzCnt, loop20HzCnt , loop10HzCnt;

extern int Balance_Pwm,Velocity_Pwm,Turn_Pwm;

extern float Mechanical_angle;

extern SysClock;
/*************************************************************************************************************/

/* Hardward Initial */
static void prvSetupHardware(void)
{
	u8 ret = 0;
	/* SystemClock Configuration, Clock source uses external crystal oscillator(HSEs), 8*9 = 72MHz */
	SystemClock_HSE(9);
	/* LED Configuration */
	LED_Configuration();
    /* Segger Configuration */
    SEGGER_RTT_Init();
	/* Systick Configuration */
	delay_init();
	/* Timer4 Configuration */
	TIM4_Int_Init(999,SysClock);//Sysclock = 589826376?
	/* IMU IIC Configuration */
	//MPU6050_IIC_Init();
	/* MPU6050 Configuration */
	//MPU6050_Init();
	/* MPU6050 DMP Configuration */
	//mpu_dmp_init();
	/* USART1 Configuration */
	Uart1_Init();
	/* USART3 Configuration */
	//Uart3_Init(9600);
    //BT_ATcmdWrite();
	/* NVIC Configuration */
	NVIC_Configuration();
	/* Bluetooth Power On */
	//BT_PowerInit();
	/* USART3 Re-Configuration */
	//Uart3_Init(115200);
	/* Encoder Configuration*/
	Encoder_Init_TIM5();
	Encoder_Init_TIM4();
	/* Init PWM 10KHZ for motor */
	//TIM1_PWM_Init(7199,0);
	delay_ms(1000);
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
	int encoder5 = 0, encoder4 = 0;

	prvSetupHardware();

    LED_Test();

	printf("\r\n Hello Wall-e. \r\n");

	//AIN2=1,			AIN1=0;
	//BIN1=0,			BIN2=1;

    //GPIO_SetBits(IMU_SCL_PORT, IMU_SCL_PIN);
    //GPIO_SetBits(IMU_SDA_PORT, IMU_SDA_PIN);
    //GPIO_ResetBits(IMU_SCL_PORT, IMU_SCL_PIN);
    //GPIO_ResetBits(IMU_SDA_PORT, IMU_SDA_PIN);

 	while(1)
	{

            //delay_ms(100);
			LED_Test();
            encoder5 = Read_Encoder(TIM5);
            encoder4 = Read_Encoder(TIM4);
            //MPU6050_Check();
            printf("encoder5 = %d encoder4 = %d\r\n",encoder5,encoder4);


           #if 0
			AIN2=1,			AIN1=0;
			BIN1=0,			BIN2=1;

			//100Hz Loop
      //if(loop100HzCnt>=10)

			if(loop200HzCnt>=5)
      {
				printf("\r\nloop200HzCnt\r\n");
      	loop100HzCnt=0;
				mpu_dmp_get_data(&pitch, &roll, &yaw);//得到欧拉角（姿态角）的数据
				ReadFromIMU();
				Encoder_Left=-Read_Encoder(2);
				Encoder_Right=Read_Encoder(4);
				Balance_Pwm =Balance_UP(pitch,Mechanical_angle,g_MPU6050Data.gyro_y);   //平衡环PID控制
				Velocity_Pwm=Velocity(Encoder_Left,Encoder_Right);       //速度环PID控制
				Moto1=Balance_Pwm-Velocity_Pwm-Turn_Pwm;                 //计算左轮电机最终PWM
				Moto2=Balance_Pwm-Velocity_Pwm+Turn_Pwm;                 //计算右轮电机最终PWM
				Xianfu_Pwm();  										   //PWM限幅
				Turn_Off(pitch);								   		   //检查角度以及电压是否正常
				Set_Pwm(Moto1,Moto2);                                    //赋值给PWM寄存器
	     }
			 #endif
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
