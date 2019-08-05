#ifndef DATA_TYPE_H__
#define DATA_TYPE_H__

typedef  unsigned char        uint8 ;
typedef  unsigned short int  uint16;
typedef  unsigned int        uint32;
typedef  signed char           sint8;
typedef  signed short int     sint16;
typedef  signed int           sint32;

typedef union
{
    uint16 val;
    uint8 adr[2];
}union_uint16;

typedef union
{
    uint32 val;
    uint8 adr[4];
}union_uint32;

#define NULL  0

#endif
