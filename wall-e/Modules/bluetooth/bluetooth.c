#include "bluetooth.h"

const char ATcmdAsk[]    =		 {"AT"};
const char ATcmdNameSet[] = 	 {"AT+NAMEWall-e"};    //Set bluetooth module name：Wall-e
const char ATcmdCodeSet[] =		 {"AT+PIN1234"};       //Set bluetooth module pin：1234
const char ATcmdRenewAsk[] = 	 {"AT+RENEW"};		   //Reset bluetooth module
const char ATcmdRenewAnswer[] = {"OK+RENEW"};	
const char ATcmdBaudSet[] =    {"AT+BAUD8"};           //Set bluetooth module baud:115200

/*******************************************************************
Function:void BT_ATcmdWrite(void)
Description:
	Setup Bluetooth:
		Name: Wall-e
		Baud: 115200
		Pin : None
Input:None
Return:None
Others:
	HM-06 module
		//The configuration of the Bluetooth 2.1 module
		baud1--->1200
		baud2--->2400
		baud3--->4800
		baud4--->9600
		baud5--->19200
		baud6--->38400
		baud7--->57600
		baud8--->115200

	HM-11 module
		//The configuration of the Bluetooth 4.0 BLE module
		//Which is difference from HM-06
		baud0--->9600
		baud4--->115200
*********************************************************************/
void BT_ATcmdWrite(void)
{
	delay_ms(100);
	Uart3SendStr("AT\r\n");
	Uart3SendStr("AT+NAMEWall-e\r\n");	 //Set bluetooth module name：Wall-e
	delay_ms(100);	
	Uart3SendStr("AT+BAUD8\r\n"); 		 //Set bluetooth module baud:115200
	delay_ms(100);		
}

/**************************************************************************
Function:void BT_PowerInit(void)
Description: 
	Bluetooth transparent transmission module power initialization function
		1. Power-on enabler: BT_EN - PB2
		2. Turn on the Bluetooth power supply: BT_EN=1
Input:None
Return:None
Others:None
***************************************************************************/
void BT_PowerInit(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB,  &GPIO_InitStructure);
  
  BT_on();
}