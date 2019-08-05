#include "all_include.h"

static u8 led_shift = 0;


void led_pin_init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	
    GPIO_InitStructure.GPIO_Pin = PIN_LED_RED;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIO_LED_RED, &GPIO_InitStructure);
/*
    GPIO_InitStructure.GPIO_Pin = PIN_LED_RED;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIO_LED_RED, &GPIO_InitStructure);
	
    GPIO_InitStructure.GPIO_Pin = PIN_LED_GREEN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIO_LED_GREEN, &GPIO_InitStructure);
*/
}

void init_led_pin_cfg(void)
{	
 	led_pin_init();
	LED_RED_OFF;
}



