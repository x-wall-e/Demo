

int main(void)	
{ 
	delay_init();	    	           //=====延时函数初始化	
	NVIC_Configuration();					 //=====中断优先级分组
	Encoder_Init_TIM2();					 //=====编码器2初始化
	Encoder_Init_TIM4();					 //=====编码器4初始化
	TIM3_Int_Init(99,7199);				 //=====10ms中断一次。电机全速运行时编码器最大值为90		
//	TIM3_Int_Init(49,7199);			   //=====5ms中断一次。电机全速运行时编码器最大值为45
  while(1)	
	{
			delay_ms(50);				 			 						//=====50ms刷一次屏幕即可,不需要一直刷新。
			printf("Encoder_Left=%d,Encoder_Right=%d\n",Encoder_Left,Encoder_Right);
		  /*也可以使用电脑上位机查看,如果没有购买OLED屏幕的客户打开电脑上位机,使用串口打印到上位机即可查看***/		
	} 				
}
