#ifndef __FLASH_H
#define __FLASH_H

#include "data_type.h"
#include "stm32f10x_flash.h"
#include "stdio.h"

//用户根据自己的需要设置
//#define STM32_FLASH_SIZE 512 	 		//所选STM32的FLASH容量大小(单位为K)
#define STM32_FLASH_SIZE 64
#define STM32_FLASH_WREN 1              //使能FLASH写入(0，不是能;1，使能)

//FLASH起始地址
#define STM32_FLASH_BASE 0x08000000 	//STM32 FLASH的起始地址
//The relative offset to start addfress.
#define FLASH_OFFEST          0X0000FC00 // EEPROM Start Addr


u16 STMFLASH_ReadHalfWord(u32 faddr);		  //读出半字  
void STMFLASH_WriteLenByte(u32 WriteAddr,u32 DataToWrite,u16 Len);	//指定地址开始写入指定长度的数据
u32 STMFLASH_ReadLenByte(u32 ReadAddr,u16 Len);						//指定地址开始读取指定长度数据
void STMFLASH_Write(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite);		//从指定地址开始写入指定长度的数据
void STMFLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead);   		//从指定地址开始读出指定长度的数据
void Flash_Test(void);

#endif
