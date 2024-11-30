#include "Int_DS18B20.h"
#include "Dri_1Wire.h"

char Int_DS18B20_ReadTem()
{
    char tem;
    u8 ls_byte, ms_byte;
    if (Dri_1Wire_Init()) {
        Dri_1Wire_WriteByte(0xCC);
        Dri_1Wire_WriteByte(0x44);
    }
    if (Dri_1Wire_Init()) {
        Dri_1Wire_WriteByte(0xCC);
        Dri_1Wire_WriteByte(0xBE);
    }
    ls_byte = Dri_1Wire_ReadByte();
    ms_byte = Dri_1Wire_ReadByte();
    tem     = (ms_byte << 4) | (ls_byte >> 4);
    return tem;
}