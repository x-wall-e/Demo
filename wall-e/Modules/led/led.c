#include "led.h"

void LED_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC,  &GPIO_InitStructure);
  GPIO_SetBits(GPIOC,GPIO_Pin_13);
}

void LED_Off(void)
{
    GPIO_SetBits(GPIOC,GPIO_Pin_13);
}

void LED_ON(void)
{
    GPIO_ResetBits(GPIOC,GPIO_Pin_13);
}

void LED_Test(void)
{
  LED_ON();
  delay_ms(100);
  LED_Off();
  delay_ms(100);
}
