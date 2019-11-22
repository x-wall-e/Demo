#ifndef __LED_H
#define __LED_H

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "delay.h"

#define LED1_PIN GPIO_Pin_14
#define LED1_PORT GPIOC

void LED_Configuration(void);
void LED_Off(void);
void LED_ON(void);
void LED_Test(void);

#endif
