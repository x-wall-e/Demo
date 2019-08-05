#ifndef __COMMON_H
#define __COMMON_H

#include "all_include.h"
#include "iap.h"

#define ENABLE_PUTSTR 1

#define IS_AF(c)  ((c >= 'A') && (c <= 'F'))
#define IS_af(c)  ((c >= 'a') && (c <= 'f'))
#define IS_09(c)  ((c >= '0') && (c <= '9'))
#define ISVALIDHEX(c)  IS_AF(c) || IS_af(c) || IS_09(c)
#define ISVALIDDEC(c)  IS_09(c)
#define CONVERTDEC(c)  (c - '0')

#define CONVERTHEX_alpha(c)  (IS_AF(c) ? (c - 'A'+10) : (c - 'a'+10))
#define CONVERTHEX(c)   (IS_09(c) ? (c - '0') : CONVERTHEX_alpha(c))

extern uint32_t Str2Int(uint8_t *inputstr, int32_t *intnum);
extern void Int2Str(uint8_t* str, int32_t intnum);
extern uint32_t Str2Int(uint8_t *inputstr, int32_t *intnum);
extern uint32_t SerialKeyPressed(uint8_t *key);
extern void SerialPutChar(uint8_t c);
extern uint8_t GetKey(void);
extern void Serial_PutString(uint8_t *s);
extern uint8_t EraseSomePages(__IO uint32_t size, uint8_t outPutCont);

#endif
