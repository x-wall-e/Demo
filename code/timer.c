#include "stm32f10x.h"
#include "data_type.h"
#include "timer.h"
//uint32 system_tick = 0;
static unsigned int systick_count =0,systick_loop=0;

u32 TimeNumbers=0;//

#if 1
void Delay(__IO u32 ms_10)
{
	TimeNumbers = ms_10;
	while(TimeNumbers != 0);
}



void Delay_Hand(void)
{
	if(TimeNumbers > 0)
	{
		TimeNumbers--;
	}
	if( (systick_loop ++ %10)==0 )
			systick_count++ ;
}
#endif
							 

//延时nus
//nus为要延时的us数.		    								   
void delay_us(u32 nus)
{	

	Delay(nus);

}
//延时nms
//注意nms的范围
//SysTick->LOAD为24位寄存器,所以,最大延时为:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK单位为Hz,nms单位为ms
//对72M条件下,nms<=1864 
void delay_ms(u16 nms)
{
	//u16 times = nms/10;
	//if(times ==0)times=1;
	Delay(nms);
} 














