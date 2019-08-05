#ifndef __IAP_H
#define __IAP_H

#include "data_type.h"
#include "flash.h"
#include "ymodem.h"
#include "common.h"

/* Define the Flsah area size ---------------------------------*/  
#if defined (STM32F10X_MD) || defined (STM32F10X_MD_VL)
 #define PAGE_SIZE                         (0x400)    /* 1 Kbyte */
 #define FLASH_SIZE                        (0x20000)  /* 128 KBytes */
#elif defined STM32F10X_CL
 #define PAGE_SIZE                         (0x800)    /* 2 Kbytes */
 #define FLASH_SIZE                        (0x40000)  /* 256 KBytes */
#elif defined STM32F10X_HD || defined (STM32F10X_HD_VL)
 #define PAGE_SIZE                         (0x800)    /* 2 Kbytes */
 #define FLASH_SIZE                        (0x80000)  /* 512 KBytes */
#elif defined STM32F10X_XL
 #define PAGE_SIZE                         (0x800)    /* 2 Kbytes */
 #define FLASH_SIZE                        (0x100000) /* 1 MByte */
#else 
 #error "Please select first the STM32 device to be used (in stm32f10x.h)"    
#endif

/*---------- Define a parameter of a function type ------------------*/
typedef  void (*iapfun)(void);

/*----------Define the APP start address ----------------------------*/
#define FLASH_APP1_ADDR		0x08005400  	

/*---------- Keep 0x08000000-0x08005400 for IAP bootloader ----------*/


/*---------- Define the APP start address ---------------------------*/
#define ApplicationAddress    FLASH_APP1_ADDR

/*---------- Compute the FLASH upload image size --------------------*/  
#define FLASH_IMAGE_SIZE                   (uint32_t) (FLASH_SIZE - (ApplicationAddress - 0x08000000))

/*---------- Output printer switch ----------------------------------*/
#define ENABLE_PUTSTR         1


/*---------- Exported types -----------------------------------------*/
typedef  void (*pFunction)(void);


void iap_load_app(uint32 appxaddr);//Execute the app in Flash
void iap_load_appsram(uint32 appxaddr);//Execute the app in Sram
void iap_write_appbin(uint32 appxaddr,uint8 *appbuf,uint32 applen);//Start writing to the bin at the specified address
extern int8_t IAP_Update(void);
extern int8_t IAP_Update(void);
extern int8_t IAP_RunApp(void);
#endif
