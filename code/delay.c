#include "all_include.h"
#if 0
void delay_us(uint32 cnt)
{
    while(cnt--) {
        __NOP();__NOP();	__NOP();	__NOP();	__NOP(); __NOP();	__NOP();__NOP();
        __NOP();__NOP();	__NOP();	__NOP ();	__NOP(); __NOP();	__NOP();__NOP();

        __NOP();__NOP();	__NOP();	__NOP();	__NOP(); __NOP();	__NOP();__NOP();
        __NOP();__NOP();	__NOP();	__NOP();	__NOP(); __NOP();	__NOP();__NOP();

        __NOP();__NOP();	__NOP();	__NOP();	__NOP(); __NOP();	__NOP();__NOP();
        __NOP();__NOP();	__NOP();	__NOP();	__NOP(); __NOP();	__NOP();__NOP();
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
        __NOP();__NOP();	__NOP();	__NOP();	__NOP(); __NOP();	__NOP();__NOP();
        __NOP();__NOP();	__NOP();	__NOP();	__NOP(); __NOP();	__NOP();__NOP();

        __NOP();__NOP();	__NOP();	__NOP();	__NOP(); __NOP();	__NOP();__NOP();
    }
}
#endif
//void delay_ms(uint32 cnt)
//{
   // while(cnt--)
   // {
      //  delay_us(1000);
    //}
//}

void delay_s(uint32 cnt)
{
    while(cnt--)
    {
        delay_ms(1000);
    }
}

