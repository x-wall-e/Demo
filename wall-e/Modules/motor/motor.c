/********************************************
Function：void Motor_Init(void)
Description: Motor Initial
Input:None
Return:None
Others:
	AIN1 - PB14
	AIN2 - PB15
	BIN1 - PB13
	BIN2 - PB12
*********************************************/
void Motor_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	AIN1=0,AIN2=0;
	BIN1=0,BIN1=0;
}


/**********************************************************************
Function：int myabs(int a)
Description: Absolute value function
Input:
	int a
Return:
	unsigned int |a|
Others:
	Only The timer PWM register can only be assigned a positive value. 
***********************************************************************/
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}

/**********************************************************************
Function：void Set_Pwm(int moto1,int moto2)
Description: Set pwm register for moto1、moto2
Input:
	int moto1: moto1 pwm
	int moto2: moto2 pwm
Return:None
Others:None
***********************************************************************/
void Set_Pwm(int moto1,int moto2)
{
	if(moto1 < 0)	AIN2=1,			AIN1=0;
	else 	    AIN2=0,			AIN1=1;
	PWMA=myabs(moto1);
	
	if(moto2 < 0)	BIN1=0,			BIN2=1;
	else        BIN1=1,			BIN2=0;
	PWMB=myabs(moto2);	
}

void Xianfu_Pwm(void)
{
	//PWM满幅是7200 限制在7000
	if(Moto1<-7000 ) Moto1=-7000 ;
	if(Moto1>7000 )  Moto1=7000 ;
	if(Moto2<-7000 ) Moto2=-7000 ;
	if(Moto2>7000 )  Moto2=7000 ;
}

void Turn_Off(float angle, float voltage)
{
		if(angle < -40 || angle > 40)	 //倾角大于40度关闭电机
		{	                                  																		 
				Moto1=0;
				Moto2=0;
				flag_fall=1;
		}		
		else 				
				flag_fall=0;
}