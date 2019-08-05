#include "all_include.h"
#include "flash.h"
#include "iap.h"
#include "ymodem.h"


int fputc(int ch, FILE *f)
{	
	USART_SendData(USART1, (u8) ch);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);

	return ch;
}

int main(void)
{ 
	uint8_t ret = -5;
  
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x4000);
	
	init_debug_usart1_pin_cfg();
	printf("\r\n hello Start... \r\n");
 
	//Flash_Test();

  while (1)
  {		
		#if 1
		ret = IAP_Update();

		if(ret)
		{
			SerialPutString("IAP_Update done.\r\n");
		}else
		{
            printf("Run into app.\r\n");
			IAP_RunApp();
		}
		#endif
	}
}

