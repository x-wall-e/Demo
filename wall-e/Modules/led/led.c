#include "led.h"

void LED_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);

  GPIO_InitStructure.GPIO_Pin = LED1_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(LED1_PORT,  &GPIO_InitStructure);
  GPIO_ResetBits(LED1_PORT,LED1_PIN);
}

void LED_Off(void)
{
    GPIO_SetBits(LED1_PORT,LED1_PIN);
}

void LED_ON(void)
{
    GPIO_ResetBits(LED1_PORT,LED1_PIN);
}

void LED_Test(void)
{
  LED_ON();
  delay_ms(100);
  LED_Off();
  delay_ms(100);
}
