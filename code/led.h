#ifndef  __HW_LED_H
#define __HW_LED_H

#include "stm32f10x.h"
#include "data_type.h"


#define PIN_LED_RED   GPIO_Pin_11
#define GPIO_LED_RED  GPIOB

#define PIN_LED_GREEN    GPIO_Pin_8
#define GPIO_LED_GREEN GPIOB

#define LED_RED_OFF   GPIO_ResetBits(GPIO_LED_RED,PIN_LED_RED)
#define LED_RED_ON  GPIO_SetBits(GPIO_LED_RED,PIN_LED_RED)

#define LED_GREEN_ON   GPIO_ResetBits(GPIO_LED_GREEN,PIN_LED_GREEN)
#define LED_GREEN_OFF  GPIO_SetBits(GPIO_LED_GREEN,PIN_LED_GREEN)

extern void init_led_pin_cfg(void);
extern void led_test(void);
extern void FlashRunLed(void);

#endif

