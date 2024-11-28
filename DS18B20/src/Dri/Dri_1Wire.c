#include "Dri_1Wire.h"
#include <STC89C5xRC.H>
#define DQ P44

bit Dri_1Wire_Init()
{
    bit result;
    DQ = 0;
    Delay10us(48);
    DQ = 1;
    Delay10us(6);
    result = ~DQ;
    Delay10us(42);
    return result;
}

void Dri_1Wire_WriteByte(u8 byte)
{
    u8 i;
    for (i = 0; i < 8; i++) {
        DQ = 0;
        DQ = byte & 0x01;
        Delay10us(6);
        DQ = 1;
        byte >>= 1;
    }
}

u8 Dri_1Wire_ReadByte()
{
    u8 byte, i;
    byte = 0x00;
    for (i = 0; i < 8; i++) {
        DQ = 0;
        DQ = 1;
        Delay10us(1);
        byte >>= 1;
        if (DQ == 1) {
            byte |= 0x80;
        }
        Delay10us(5);
    }

    return byte;
}
