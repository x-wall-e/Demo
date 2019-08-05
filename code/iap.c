#include "iap.h"
#include "delay.h"

iapfun jump2app;
uint32_t JumpAddress;
//u16 iapbuf[1024];
uint8_t tab_1024[1024] = {0};

pFunction Jump_To_Application;

#if 0
//appxaddr : App start addr
//appbuf : App Core
//appsize : App Size(Byte)
void iap_write_appbin(u32 appxaddr,u8 *appbuf,u32 appsize)
{
	uint16 t;
	uint16 i=0;
	uint16 temp;
	uint32 fwaddr=appxaddr;//Currently written address
	uint8 *dfu=appbuf;
	for(t=0;t<appsize;t+=2)
	{
		temp=(u16)dfu[1]<<8;
		temp+=(u16)dfu[0];
		dfu+=2;//Offset 2 bytes
		iapbuf[i++]=temp;
		if(i==1024)
		{
			i=0;
			STMFLASH_Write(fwaddr,iapbuf,1024);
			fwaddr+=2048; //Offset 2048 16 = 2*8. so * 2
		}
	}
	if(i)STMFLASH_Write(fwaddr,iapbuf,i);//Write the last byte of content into it
}
#endif


/************************************************************************/
int8_t IAP_Upload(void)
{
	uint32_t status = 0; 
	SerialPutString("\n\n\rSelect Receive File ... (press any key to abort)\n\r");
	if (GetKey() == CRC16)
	{
		status = Ymodem_Transmit((uint8_t*)ApplicationAddress, (const uint8_t*)"UploadedFlashImage.bin", FLASH_IMAGE_SIZE);
		if (status != 0) 
		{
			SerialPutString("\n\rError Occured while Transmitting File\n\r");
			return -1;
		}
		else
		{
			SerialPutString("\n\rFile Trasmitted Successfully \n\r");
			return -2;
		}
	}
	else
	{
		SerialPutString("\r\n\nAborted by user.\n\r");  
		return 0;
	}
}

/************************************************************************/
int8_t IAP_Update(void)
{
	uint8_t Number[10] = "";
	int32_t Size = 0;
	Size = Ymodem_Receive(&tab_1024[0]);
	if (Size > 0)
	{
		SerialPutString("\r\n Update Over!\r\n");
		SerialPutString(" Name: ");
		SerialPutString(file_name);
		Int2Str(Number, Size);
		SerialPutString("\r\n Size: ");
		SerialPutString(Number);
		SerialPutString(" Bytes.\r\n");
        IAP_RunApp();
		return 0;
	}
	else if (Size == -1)
	{
		SerialPutString("\r\n Image Too Big!\r\n");
		return -1;
	}
	else if (Size == -2)
	{
		SerialPutString("\r\n Update failed!\r\n");
		return -2;
	}
	else if (Size == -3)
	{
		SerialPutString("\r\n Aborted by user.\r\n");
		return -3;
	}
	else
	{
		SerialPutString(" Receive Filed.\r\n");
		return -4;
	}
}


int8_t IAP_RunApp(void)
{
    if(((*(vu32*)(FLASH_APP1_ADDR+4))&0xFF000000)==0x08000000)//Determine if it is 0x08000000
    {
        //Execute the app in Flash
    	if (((*(__IO uint32_t*)ApplicationAddress) & 0x2FFE0000 ) == 0x20000000)//Check if the top address of the stack is legal
    	{   
        //  __set_PRIMASK(1);// Disable global interrupt
        //	__disable_irq();//Disable global interrupt,Must be turned on at app
        //  __disable_fault_irq();//Turn off all default interrupts,Must be turned on at app
    		SerialPutString("\r\n Run to app.\r\n");
    		JumpAddress = *(__IO uint32_t*) (ApplicationAddress + 4);//The second word in the user code area is the application start address (reset address)
    		Jump_To_Application = (pFunction) JumpAddress;
    		__set_MSP(*(__IO uint32_t*) ApplicationAddress);//Initialize the App stack pointer (the first word in the user code area is used to store the top address of the stack)
    		Jump_To_Application();//Jump to App
    		return 0;
    	}
    	else
    	{
    		SerialPutString("\r\n Run to app error.\r\n");
    		return -1;
    	}
    }else{
        SerialPutString("Illegal FLASH APP!\r\n");   
    }
}


