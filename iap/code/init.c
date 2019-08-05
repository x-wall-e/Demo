#include "all_include.h"

void SysTick_Configuration(void)
{
    SysTick_Config(SystemCoreClock / 1000);// 20ms
}

void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    #ifdef  VECT_TAB_RAM
    // Set the Vector Table base location at 0x20000000
    NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);
    #else  /* VECT_TAB_FLASH  */
    // Set the Vector Table base location at 0x08000000
   // NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x08004000);
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x8004000);
    #endif

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	/* Enable the USART1 Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

	 __enable_irq();
     __enable_fault_irq(); 
}

void IWDG_Configuration(void)
{
    IWDG_Enable();// Enable the IWDG//
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable); // Enable the access to the IWDG registers//
    /*
    //   IWDG_SetPrescaler(IWDG_Prescaler_4);//400MS
    //   IWDG_SetPrescaler(IWDG_Prescaler_8);//819.2ms
       IWDG_SetPrescaler(IWDG_Prescaler_16);//1638.4ms
       IWDG_SetPrescaler(IWDG_Prescaler_32);//3276.8ms
       IWDG_SetPrescaler(IWDG_Prescaler_64);//6553.6ms
       IWDG_SetPrescaler(IWDG_Prescaler_128);//13107.2ms
       //IWDG_SetPrescaler(IWDG_Prescaler_256);//26214.4ms //Fixe IWDG Reset period //
    */
    IWDG_SetPrescaler(IWDG_Prescaler_64);//6553.6ms

    IWDG_SetReload(0x0FFF);//
    IWDG_ReloadCounter();// Refresh IWDG //
}

void IWDG_Refresh(void)
{
	#if EN_IWDG == 0x01
    IWDG_ReloadCounter();
    #endif
}

void init_peripheral(void)
{
	//抵达定时器配置
	SysTick_Configuration();

	//中断配置
	NVIC_Configuration();

	//LED引脚配置
	init_led_pin_cfg();
	LED_RED_ON;

	//电源控制引脚配置
	PowerCtrlPinConfig();

	//调试串口1引脚配置
	init_debug_usart1_pin_cfg();
	
	//读卡模块与主控通讯串口3配置
	init_comm_usart3_pin_cfg();

	//RTC时钟配置
	RTC_Config();	

	//eeprom配置
	init_eeprom_pin_cfg();
	
	//BKP配置
	//system_bkp_config();

	//SPI1_Init();

	#if EN_IWDG == 0x01
//    IWDG_Configuration();
	#endif	
}

void dev_self_test(void)
{
	//readertest.rfic = rc531_self_test();
	readertest.eeprom = eeprom_self_test();
	//readertest.psamsta = sam_init();
}

u8 init_data(void)
{	
	PackTestInfo(&readertest);

	return OPSUCCESS;
	
}

