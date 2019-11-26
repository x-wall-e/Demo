#include "usart1.h"
#include <errno.h>
#include <sys/unistd.h>


static void USART_GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;// PA9复用为发送
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}
/*************************************
函数名：void Uart1_Init(void)
说明：USART初始化
入口：无
出口：无
备注：无
*************************************/
void Uart1_Init(void)
{
    USART_InitTypeDef USART_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    USART_GPIO_Configuration();
    USART_InitStructure.USART_BaudRate = 9600;                                          // 波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;                         // 数据长度，如果有奇偶校验，则字长必须为9bits，参见stm32f10x_usart.h Line63
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                              // 停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;                                 // 奇偶校验
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;     // 硬件控制流
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                     // 发送/接收模式
    USART_Init(USART1, &USART_InitStructure);                                           // 初始化USARTx

    //USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);                                      // 使能串口1的DMA发送
    USART_Cmd(USART1, ENABLE);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);                                      // 使能USARTx
}

/*********************************
函数名：void Uartx_PutChar(u8 ch)
说明：串口1发送字符
入口：u8 ch  需要发送的字符
出口：无
备注：无
*********************************/
//void Uart1_PutChar(const u8 ch)
void Uart1_PutChar(u8 ch)
{
    USART_SendData(USART1, (u8)ch);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

/**********************************************
函数名：void Uartx_PutString(u8 * buf, u8 len)
说明：串口x发送字符串
入口：u8* buf  字符串数组
			u8 len 字符个数
出口：无
备注：无
*********************************************/
//void Uart1_PutString(const u8 * buf, const u8 len)
void Uart1_PutString(u8 * buf, const u8 len)

{
    u8 i;

    for(i = 0; i < len; i++)
    	Uart1_PutChar(*buf++);
}


u8 USART_GetChar(void)
{
    while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
    return (u8)USART_ReceiveData(USART1);
}

#if 0
int _read(int file, char *ptr, int len)
{
    int i;
    int num = 0;
    char ch;

    switch (file)
    {
        case STDIN_FILENO:
        {
            for (i = 0; i < len; i++)
            {
                ch = USART_GetChar();
                *ptr++ = ch;
                num++;
            }
            break;
        }
        default:
        {
            errno = EBADF;
            return -1;
        }
    }

    return num;
}

int _write(int file, char *ptr, int len)
{
    int i;

    switch (file)
    {
        case STDOUT_FILENO:
        {
            for (i = 0; i < len; i++)
            {
                Uart1_PutChar(*ptr++ & (u16)0x01FF);
            }
            break;
        }
        case STDERR_FILENO:
        {
            for (i = 0; i < len; i++)
            {
                Uart1_PutChar(*ptr++ & (u16)0x01FF);
            }
            break;
        }
        default:
        {
            errno = EBADF;
            return -1;
        }
    }

    return len;
}
#endif
