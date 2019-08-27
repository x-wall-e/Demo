#include "control.h"

int Balance_Pwm,Velocity_Pwm,Turn_Pwm;

float Mechanical_angle=-6; 	//机械中值。

float balance_UP_KP=280; 	//直立环KP
float balance_UP_KD=0.8;

float velocity_KP=90;
float velocity_KI=0.45;

//直立PD控制
//角度、机械平衡角度（机械中值）、角速度
int Balance_UP(float Angle,float Mechanical_balance,float Gyro)
{  
	float Bias;
	int balance;
	Bias = Angle - Mechanical_balance; //求出平衡的角度中值和机械相关
	balance = balance_UP_KP * Bias + balance_UP_KD * Gyro;  //计算平衡控制的电机PWM  PD控制   kp是P系数 kd是D系数 
	return balance;
}

//速度PI控制
//电机编码器的值
//速度控制PWM
int velocity(int encoder_left,int encoder_right)
{  
	static float Velocity,Encoder_Least,Encoder,Movement;
	static float Encoder_Integral;
	if(1==Flag_Qian)				
	{
		Movement=20;
	}
	else if(1==Flag_Hou)//接收到蓝牙APP遥控数据		
	{
		Movement=-20;//设定速度
	}
	else//没有收到任何数据
	{	
		Movement=0;
	}
	//速度PI控制器
	Encoder_Least =(Encoder_Left+Encoder_Right)-0;//获取最新速度偏差==测量速度（左右编码器之和）-目标速度（此处为零） 
	Encoder *= 0.8;	//一阶低通滤波器       
	Encoder += Encoder_Least*0.2;//一阶低通滤波器    
	Encoder_Integral += Encoder;  //积分出位移 积分时间：10ms
	Encoder_Integral = Encoder_Integral - Movement; //接收遥控器数据，控制前进后退
	if(Encoder_Integral>10000)  	Encoder_Integral=10000; //积分限幅
	if(Encoder_Integral<-10000)		Encoder_Integral=-10000; //积分限幅	
	Velocity = Encoder * velocity_KP + Encoder_Integral * velocity_KI;//速度控制	
	if(pitch<-40||pitch>40) 			Encoder_Integral=0;//电机关闭后清除积分
	return Velocity;
}

