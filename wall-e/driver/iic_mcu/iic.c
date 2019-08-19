#include "iic.h"

/*************************************
Function：void IIC_Init(void)
Description：iic initialization
Input:None
Return:None
Others:None
*************************************/
void IIC_Init(void)
{
    GPIO_SetBits(GPIOB, GPIO_Pin_6| GPIO_Pin_7);
}


/*************************************
Function：void IIC_Start(void)
Description：Generate iic start signal
Input:None
Return:None
Others:None
*************************************/
void IIC_Start(void)
{
    SDA_OUT();//SDA is set to output 
    IIC_SDA_H;
    IIC_SCL_H;
    Delay_us(4);
    IIC_SDA_L;
    //Delay_us(1);
    IIC_SCL_L;//Hold the clock line SCL LOW and prepare to send or receive data
}

/************************************
Function：void IIC_Stop(void)
Description：Generate iic stop signal
Input:None
Return:None
Others:None
************************************/
void IIC_Stop(void)
{
    SDA_OUT();// SDA is set to output 
    IIC_SDA_L;
    Delay_us(4);
    IIC_SCL_H;
    //Delay_us(1);
    IIC_SDA_H;// Send I2C bus end signal
    Delay_us(5);// Start again requires 4.7us
}

/*****************************************************
Function：u8 IIC_Wait_Ack(void)
Description：Waiting for the response signal to arrive.
Input:None
Return:None
Others:None
******************************************************/
u8 IIC_Wait_Ack(void)
{
    u8 ucErrTime = 0;
    
    SDA_IN();                   // SDA is set to input 
    IIC_SDA_H;
    //Delay_us(1);       
    IIC_SCL_H;
    //Delay_us(1);     
    while (READ_SDA)            // SDA is high, waiting for the IIC device to pull low  
    {
        ucErrTime++;
        if (ucErrTime > 250)    // 40*250=1ms did not reply, IIC master send a stop signal      
        {
            IIC_Stop();
            return 1;
        }
    }
    IIC_SCL_L;
    return 0;
}

/*********************************
Function：void IIC_Ack(void)
Description：Generate Ack response
Input:None
Return:None
Others:None
*********************************/
void IIC_Ack(void)
{
    IIC_SCL_L;
    SDA_OUT();
    IIC_SDA_L;
    //Delay_us(1);
    IIC_SCL_H;
    //Delay_us(1);
    IIC_SCL_L;
}

/*********************************
Function：void IIC_NAck(void)
Description：Generate NAck response
Input:None
Return:None
Others:None
*********************************/
void IIC_NAck(void)
{
    IIC_SCL_L;
    SDA_OUT();
    IIC_SDA_H;
    //Delay_us(1);
    IIC_SCL_H;
    //Delay_us(1);
    IIC_SCL_L;
}

/*********************************
Function：void IIC_Send_Byte(u8 txd)
Description：iic send a byte.
Input:u8 txd
Return:None
Others:None
*********************************/
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;  
    
    SDA_OUT();      
    IIC_SCL_L;     //The High or Low state of the data line can only change whe the clock signal on the SCL line is LOW
    for (t = 0; t < 8; t++)
    {              
            if ((txd&0x80) >> 7)
                IIC_SDA_H;
            else
                IIC_SDA_L;
            txd <<= 1;    
            //Delay_us(1);
            IIC_SCL_H;
            //Delay_us(1); 
            IIC_SCL_L;
    }
    IIC_Wait_Ack();
}

/*********************************
Function：u8 IIC_Read_Byte(u8 ack)
Description：iic read a byte.
Input:u8 ack 	ack=1，send ACK
				ack=0，send nACK
Return:u8 		1，has ack
				0，has nACK	
Others: Return the slave's response
*********************************/
u8 IIC_Read_Byte(u8 ack)
{
    u8 i, receive = 0;
    
    SDA_IN();   // 设置为输入
    for (i = 0; i < 8; i++)
    {
        IIC_SCL_L; 
        //Delay_us(1);
        IIC_SCL_H;
        receive <<= 1;
        if (READ_SDA)       // 1
            receive++;
        //Delay_us(1); 
    }                  
    if (!ack)
            IIC_NAck();     // send nACK
    else
            IIC_Ack();      // send ACK   
    return receive;
}


