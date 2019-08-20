#ifndef __BLUETOOTH_H
#define __BLUETOOTH_H

#include <stdio.h>
#include "usart3.h"
#include "delay.h"

#define BT_on()      {GPIO_SetBits(GPIOB, GPIO_Pin_1);printf("BT power init success...\r\n");}
#define BT_off()     {GPIO_ResetBits(GPIOB, GPIO_Pin_1);printf("BT power close success...\r\n");}

extern void BT_ATcmdWrite(void);
extern void BT_PowerInit(void);
#endif
