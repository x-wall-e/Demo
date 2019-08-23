#include "i2c.h"

/******************************************************
Function：static void OLED_IIC_GPIO_Configuration(void)
Description：iic gpio configuration
Input:None
Return:None
Others:None
*******************************************************/
static void OLED_IIC_GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;// PB10,11-->IIC2
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;// 推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;// 50MHz翻转频率
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/****************************************
Function：void OLED_IIC_Init(void)
Description：iic initialization
Input:None
Return:None
Others:None
*****************************************/
void OLED_IIC_Init(void)
{
    OLED_IIC_GPIO_Configuration();

    GPIO_SetBits(GPIOB, GPIO_Pin_10| GPIO_Pin_11);
}


/********************************
Function：void OLED_IIC_Start(void)
Description：Generate iic start signal
Input:None
Return:None
Others:None
*********************************/
void OLED_IIC_Start(void)
{
    SDA_OUT();/* SDA is set to output */
    IIC_SDA_H;
    IIC_SCL_H;
    delay_us(4);
    IIC_SDA_L;
    delay_us(1);
    IIC_SCL_L; /* Hold the clock line SCL LOW and prepare to send or receive data */
}

/************************************
Function：void OLED_IIC_Stop(void)
Description：Generate iic stop signal
Input:None
Return:None
Others:None
************************************/
void OLED_IIC_Stop(void)
{
    SDA_OUT();/* SDA is set to output */
    IIC_SDA_L;
    delay_us(4);
    IIC_SCL_H;
    delay_us(1);
    IIC_SDA_H;
    delay_us(5);/* Start again requires 4.7us */
}

/*****************************************************
Function：u8 IIC_Wait_Ack(void)
Description：Waiting for the response signal to arrive.
Input:None
Return:u8	1: receive ACK fail
			0: receive ACK success
Others:None
******************************************************/
u8 OLED_IIC_Wait_Ack(void)
{
    u8 ucErrTime = 0;

    SDA_IN(); /* SDA is set to input */

    IIC_SDA_H;
    delay_us(1);
    IIC_SCL_H;
    delay_us(1);

    while (READ_SDA) /* SDA is high, waiting for the IIC device to pull low */
    {
        ucErrTime++;
        if (ucErrTime > 250) /* 40*250=1ms did not reply, IIC master send a stop signal */
        {
            OLED_IIC_Stop();
            return 1;
        }
    }
    IIC_SCL_L;
    return 0;
}

/********************************
Function：void OLED_IIC_Ack(void)
Description：Generate Ack response
Input:None
Return:None
Others:None
*********************************/
void OLED_IIC_Ack(void)
{
    IIC_SCL_L;
    SDA_OUT();
    IIC_SDA_L;
    delay_us(1);
    IIC_SCL_H;
    delay_us(1);
    IIC_SCL_L;
}

/********************************
Function：void OLED_IIC_NAck(void)
Description：Generate NAck response
Input:None
Return:None
Others:None
*********************************/
void OLED_IIC_NAck(void)
{
    IIC_SCL_L;
    SDA_OUT();
    IIC_SDA_H;
    delay_us(1);
    IIC_SCL_H;
    delay_us(1);
    IIC_SCL_L;
}

/***************************************
Function：void OLED_IIC_Send_Byte(u8 txd)
Description：iic send a byte.
Input:u8 txd
Return:None
Others:None
***************************************/
void OLED_IIC_Send_Byte(u8 txd)
{
    u8 t;

    SDA_OUT();

    IIC_SCL_L; /* The High or Low state of the data line can only change whe the clock signal on the SCL line is LOW */

	for (t = 0; t < 8; t++)
    {
            if ((txd & 0x80) >> 7) /* MSB */
                IIC_SDA_H;
            else
                IIC_SDA_L;
            txd <<= 1;
            delay_us(1);
            IIC_SCL_H;
            delay_us(1);
            IIC_SCL_L;
    }
    IIC_Wait_Ack();
}

/**************************************
Function：u8 OLED_IIC_Read_Byte(u8 ack)
Description：iic read a byte.
Input:u8 ack 	ack=1，send ACK
				ack=0，send nACK
Return:u8 		1，has ack
				0，has nACK
Others: Return the slave's response
**************************************/
u8 OLED_IIC_Read_Byte(u8 ack)
{
    u8 i, receive = 0;

    SDA_IN();/* SDA is set to input */

    for (i = 0; i < 8; i++)
    {
        IIC_SCL_L;
        delay_us(1);
        IIC_SCL_H;
        receive <<= 1;
        if (READ_SDA)       // 1
            receive++;
        delay_us(1);
    }
    if (!ack)
            IIC_NAck();     // send nACK
    else
            IIC_Ack();      // send ACK
    return receive;
}