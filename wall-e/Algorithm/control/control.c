#include "control.h"

extern int 	Flag_Forward,Flag_Backward,Flag_Left,Flag_Right;
extern int   Encoder_Left,Encoder_Right;
extern float pitch, roll, yaw;
extern short gyrox,gyroy,gyroz;
extern int     Moto1,Moto2;
extern u8    flag_UltrasonicWave;

int Balance_Pwm,Velocity_Pwm,Turn_Pwm;

float Mechanical_angle=0; //机械中值
//float balance_UP_KP=300; 	 // 小车直立环PD参数
//float balance_UP_KD=1.9;//

float balance_UP_KP=350; 	 // 小车直立环PD参数
float balance_UP_KD=1.0;

float velocity_KP=-90;     // 小车速度环PI参数
float velocity_KI=-0.45;



void EXTI9_5_IRQHandler(void) 
{    
    if(PBin(5)==0)
    {		
        EXTI->PR=1<<5;                                           //===清除LINE5上的中断标志位   
        mpu_dmp_get_data(&pitch,&roll,&yaw);                     //===得到欧拉角（姿态角）的数据
        MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);                 //===得到陀螺仪数据
        //printf(">> pitch=%.2f,roll=%.2f,yaw=%.2f\n",pitch,roll,yaw);
        Encoder_Left=-Read_Encoder(2);                           //===读取编码器的值，因为两个电机的旋转了180度的，所以对其中一个取反，保证输出极性一致
        Encoder_Right=Read_Encoder(4);                           //===读取编码器的值
        Balance_Pwm =balance_UP(pitch,Mechanical_angle,gyroy);   //===平衡环PID控制	
        Velocity_Pwm=velocity(Encoder_Left,Encoder_Right);       //===速度环PID控制	 
        if(1==Flag_Left||1==Flag_Right)    
        Turn_Pwm =turn(Encoder_Left,Encoder_Right,gyroz);        //===转向环PID控制
        else Turn_Pwm=0.5*gyroz;
        Moto1=Balance_Pwm-Velocity_Pwm-Turn_Pwm;                 //===计算左轮电机最终PWM
        Moto2=Balance_Pwm-Velocity_Pwm+Turn_Pwm;                 //===计算右轮电机最终PWM
        Xianfu_Pwm();                                            //===PWM限幅
        //Turn_Off(pitch);                                       //===检查角度以及电压是否正常
        Set_Pwm(Moto1,Moto2);                                    //===赋值给PWM寄存器         
    }       	
} 

/**************************************************************************
函数功能：直立PD控制
入口参数：角度、机械平衡角度（机械中值）、角速度
返回  值：直立控制PWM
**************************************************************************/
int balance_UP(float Angle,float Mechanical_balance,float Gyro)
{  
    float Bias;
    int balance;
    Bias=Angle-Mechanical_balance;                      //===求出平衡的角度中值和机械相关
    balance=balance_UP_KP*Bias+balance_UP_KD*Gyro;      //===计算平衡控制的电机PWM  PD控制   kp是P系数 kd是D系数 
    return balance;
}

/**************************************************************************
函数功能：速度PI控制
入口参数：电机编码器的值
返回  值：速度控制PWM
**************************************************************************/
int velocity(int encoder_left,int encoder_right)
{  
    static float Velocity,Encoder_Least,Encoder,Movement;
    static float Encoder_Integral;
    if(1==Flag_Forward)				
    {
        flag_UltrasonicWave=0;//无论前面是否有障碍物,蓝牙遥控优先级最高。将标志位置0
        Movement=-150;
    }
    else if(1==Flag_Backward)//接收到蓝牙APP遥控数据		
    {
        flag_UltrasonicWave=0;//无论前面是否有障碍物,蓝牙遥控优先级最高。将标志位置0
        Movement=150;//设定速度
    }
    /*当超声波的距离低于10cm时,即10cm处存在障碍物,将超声波标志位置并且赋积分值使其后退,这里做了个简单的P比例计算*/
    //else if(UltrasonicWave_Distance<10&&UltrasonicWave_Distance>3)
    //{
    //	flag_UltrasonicWave=1;
    //	Movement=UltrasonicWave_Distance*50;		
    //}
    else//没有接受到任何的数据
    {	
        flag_UltrasonicWave=0;
        Movement=0;
    }
    //=============速度PI控制器=======================//	
    Encoder_Least =(Encoder_Left+Encoder_Right)-0;                      //===获取最新速度偏差==测量速度（左右编码器之和）-目标速度（此处为零） 
    Encoder *= 0.8;		                                                //===一阶低通滤波器       
    Encoder += Encoder_Least*0.2;	                                    //===一阶低通滤波器    
    Encoder_Integral +=Encoder;                                         //===积分出位移 积分时间：10ms
    Encoder_Integral=Encoder_Integral-Movement;                         //===接收遥控器数据，控制前进后退
    if(Encoder_Integral>10000)  	Encoder_Integral=10000;             //===积分限幅
    if(Encoder_Integral<-10000)		Encoder_Integral=-10000;            //===积分限幅	
    Velocity=Encoder*velocity_KP+Encoder_Integral*velocity_KI;          //===速度控制	
    if(pitch<-40||pitch>40) 			Encoder_Integral=0;             //===电机关闭后清除积分
    return Velocity;
}
/**************************************************************************
函数功能：转向PD控制
入口参数：电机编码器的值、Z轴角速度
返回  值：转向控制PWM
**************************************************************************/
int turn(int encoder_left,int encoder_right,float gyro)//转向控制
{
    static float Turn_Target,Turn,Encoder_temp,Turn_Convert=0.9,Turn_Count;
    float Turn_Amplitude=100,Kp=20,Kd=0;     
    //=============遥控左右旋转部分=======================//
    //这一部分主要是根据旋转前的速度调整速度的起始速度，增加小车的适应性
    if(1==Flag_Left||1==Flag_Right)                      
    {
        if(++Turn_Count==1)
        Encoder_temp=myabs(encoder_left+encoder_right);      
        Turn_Convert=55/Encoder_temp;
        if(Turn_Convert<0.6)Turn_Convert=0.6;
        if(Turn_Convert>3)Turn_Convert=3;
    }	
    else
    {
        Turn_Convert=0.9;
        Turn_Count=0;
        Encoder_temp=0;
    }			
    if(1==Flag_Left)	           Turn_Target+=Turn_Convert;
    else if(1==Flag_Right)	     Turn_Target-=Turn_Convert; 
    else Turn_Target=0;
    if(Turn_Target>Turn_Amplitude)  Turn_Target=Turn_Amplitude;    //===转向	速度限幅
    if(Turn_Target<-Turn_Amplitude) Turn_Target=-Turn_Amplitude;
    if(Flag_Forward==1||Flag_Backward==1)  Kd=0.5;        
    else Kd=0;   //转向的时候取消陀螺仪的纠正 有点模糊PID的思想
    //=============转向PD控制器=======================//
    Turn=-Turn_Target*Kp-gyro*Kd;                 //===结合Z轴陀螺仪进行PD控制
    return Turn;
}
