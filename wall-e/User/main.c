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
#include "pwm.h"
#include "sys.h"
#include "SEGGER_RTT.h"
#include "SEGGER_RTT_Conf.h"

/**********************************Global Variable***********************************************************/
int Flag_Forward,Flag_Backward,Flag_Left,Flag_Right;
float pitch = 0.0,roll = 0.0,yaw = 0.0;
short  gyrox,gyroy,gyroz;//陀螺仪数据
int     Moto1=0,Moto2=0;
u8    flag_fall=0;
int   Encoder_Left,Encoder_Right;
u8    flag_UltrasonicWave=0;


/* Control frequency */
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
    /* Systick Configuration */
    delay_init();
    /* USART1 Configuration */
    Uart1_Init();
    /* MPU6050 Configuration */
    MPU_Init();
    /* MPU6050 DMP Configuration */
    mpu_dmp_init();
    /* NVIC Configuration */
    NVIC_Configuration();
    /* Encoder Configuration*/
    Encoder_Init_TIM2();
    Encoder_Init_TIM4();
    /* Init PWM 10KHZ for motor */
    TIM1_PWM_Init(7199,0);
    /* Motor io Configuration */
    Motor_Init();
    /* MPU6050 INT Pin Configuration */
    MPU6050_EXTI_Init();
    /* Segger Configuration */
    SEGGER_RTT_Init();

}

int main(void)
{
    prvSetupHardware();

    while(1)
    {
        LED_Test();
    }

}
