#include "Int_EEPROM.h"
#include "Dri_IIC.h"

#define DEV_ADDR  0xA0
#define PAGE_SIZE 16

// 写入一页
void Int_EEPROM_WritePage(u8 addr, u8 bytes[], u8 len)
{
    u8 i;
    Dri_IIC_Start();
    Dri_IIC_SendByte(DEV_ADDR);
    Dri_IIC_ReceiveAck();
    Dri_IIC_SendByte(addr);
    Dri_IIC_ReceiveAck();
    for (i = 0; i < len; i++) {
        Dri_IIC_SendByte(bytes[i]);
        Dri_IIC_ReceiveAck();
    }
    Dri_IIC_Stop();
    Com_Util_Delay1ms(5);
}

// 写入一组数据  循环写法
// void Int_EEPROM_WriteBytes(u8 addr, u8 bytes[], u8 len)
// {
//     u8 pageIndex, index, surplusLen;
//     pageIndex  = addr & 0xF0;
//     index      = addr & 0x0F;
//     surplusLen = len;
//     while (surplusLen != 0) {
//         if ((16 - index) < surplusLen) {
//             Int_EEPROM_WritePage((pageIndex + index), bytes, (16 - index));
//             surplusLen = surplusLen - (16 - index);
//             bytes += (16 - index);
//             pageIndex += 0x10;
//             index = 0;
//         } else {
//             Int_EEPROM_WritePage((pageIndex + index), bytes, surplusLen);
//             surplusLen = 0;
//         }
//     }
// }

// 写入一组数据  递归写法
void Int_EEPROM_WriteBytes(u8 addr, u8 bytes[], u8 len)
{
    u8 page_reamain = PAGE_SIZE - (addr % PAGE_SIZE);
    if (page_reamain < len) {
        // 当前页不足
        // 写入当前页
        Int_EEPROM_WritePage(addr, bytes, page_reamain);
        // 写入下一页
        Int_EEPROM_WritePage(addr + page_reamain, bytes + page_reamain, len - page_reamain);
    } else {
        // 当前页充足
        Int_EEPROM_WritePage(addr, bytes, len);
    }
}

void Int_EEPROM_ReadBytes(u8 addr, u8 bytes[], u8 len)
{
    u8 i;
    // 先伪写，写入读取的开始地址
    Dri_IIC_Start();
    Dri_IIC_SendByte(DEV_ADDR);
    Dri_IIC_ReceiveAck();
    Dri_IIC_SendByte(addr);
    Dri_IIC_ReceiveAck();
    // 再读取
    Dri_IIC_Start();
    Dri_IIC_SendByte(DEV_ADDR + 1);
    Dri_IIC_ReceiveAck();
    for (i = 0; i < len; i++) {
        bytes[i] = Dri_IIC_ReceiveByte();
        Dri_IIC_SendAck(i == (len - 1) ? 1 : 0);
    }
    Dri_IIC_Stop();
}
