#ifndef __EXTI_H
#define __EXIT_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"
#include "misc.h"
#include "sys.h"

#define INT PBin(5)

void MPU6050_EXTI_Init(void);
#endif
