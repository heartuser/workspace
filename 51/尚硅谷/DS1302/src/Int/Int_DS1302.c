#include "Int_DS1302.h"
#include <STC89C5xRC.H>

#define SCLK        P37
#define IO          P40
#define CE          P41

#define SECOND      0x80
#define MINUTE      0x82
#define HOUR        0x84
#define DAY         0x86
#define MONTH       0x88
#define DAY_OF_WEEK 0x8A
#define YEAR        0x8C
#define WP          0x8E

void Int_DS1302_WriteByte(u8 cmd_byte, u8 data_byte)
{
    u8 i;
    CE = 1;
    for (i = 0; i < 8; i++) {
        IO = cmd_byte & 0x01;
        cmd_byte >>= 1;
        SCLK = 1;
        SCLK = 0;
    }

    for (i = 0; i < 8; i++) {
        IO = data_byte & 0x01;
        data_byte >>= 1;
        SCLK = 1;
        SCLK = 0;
    }

    CE = 0;
}

u8 Int_DS1302_ReadByte(u8 cmd_byte)
{
    u8 byte, i;
    CE = 1;
    for (i = 0; i < 8; i++) {
        IO = cmd_byte & 0x01;
        cmd_byte >>= 1;
        SCLK = 1;
        if (i != 7) {
            SCLK = 0;
        }
    }

    for (i = 0; i < 8; i++) {
        SCLK = 0;
        byte >>= 1;
        if (IO == 1) {
            byte |= 0x80;
        }
        // byte |= (IO << i);
        SCLK = 1;
    }

    CE = 0;
    return byte;
}

void Int_DS1302_Init()
{
    CE   = 0;
    IO   = 0;
    SCLK = 0;
}

void Int_DS1302_SetDate(Struct_Date *p_st_date)
{
    u8 byte;
    // 关闭写保护
    Int_DS1302_WriteByte(WP, 0x00);
    // 设置秒
    byte = ((p_st_date->second / 10) << 4) | (p_st_date->second % 10);
    Int_DS1302_WriteByte(SECOND, byte);
    // 设置分钟
    byte = ((p_st_date->minute / 10) << 4) | (p_st_date->minute % 10);
    Int_DS1302_WriteByte(MINUTE, byte);
    // 设置小时(24小时制)
    byte = ((p_st_date->hour / 10) << 4) | (p_st_date->hour % 10);
    Int_DS1302_WriteByte(HOUR, byte);
    // 设置日期
    byte = ((p_st_date->day / 10) << 4) | (p_st_date->day % 10);
    Int_DS1302_WriteByte(DAY, byte);
    // 设置月份
    byte = ((p_st_date->month / 10) << 4) | (p_st_date->month % 10);
    Int_DS1302_WriteByte(MONTH, byte);
    // 设置星期
    byte = p_st_date->day_of_week;
    Int_DS1302_WriteByte(DAY_OF_WEEK, byte);
    // 设置年份
    byte = ((p_st_date->year / 10) << 4) | (p_st_date->year % 10);
    Int_DS1302_WriteByte(YEAR, byte);
    // 开启写保护
    Int_DS1302_WriteByte(WP, 0x80);
}

void Int_DS1302_GetDate(Struct_Date *p_st_date)
{
    u8 byte;
    // 获取秒
    byte              = Int_DS1302_ReadByte(SECOND + 1);
    p_st_date->second = ((byte >> 4) * 10) + (byte & 0x0F);
    // 获取分钟
    byte              = Int_DS1302_ReadByte(MINUTE + 1);
    p_st_date->minute = ((byte >> 4) * 10) + (byte & 0x0F);
    // 获取小时（24小时制）
    byte            = Int_DS1302_ReadByte(HOUR + 1);
    p_st_date->hour = ((byte >> 4) * 10) + (byte & 0x0F);
    // 获取日期
    byte           = Int_DS1302_ReadByte(DAY + 1);
    p_st_date->day = ((byte >> 4) * 10) + (byte & 0x0F);
    // 获取月份
    byte             = Int_DS1302_ReadByte(MONTH + 1);
    p_st_date->month = ((byte >> 4) * 10) + (byte & 0x0F);
    // 获取星期
    byte                   = Int_DS1302_ReadByte(DAY_OF_WEEK + 1);
    p_st_date->day_of_week = byte;
    // 获取年份
    byte            = Int_DS1302_ReadByte(YEAR + 1);
    p_st_date->year = ((byte >> 4) * 10) + (byte & 0x0F);
}
