#ifndef __INT_EEPROM_H__
#define __INT_EEPROM_H__

#include "Com_Util.h"

/**
 * @brief 写入一段字节
 * 
 * @param addr 写入的起始地址
 * @param byte 要写入的字节数组
 * @param len 要写入的字节数组的长度
 */
void Int_EEPROM_WriteBytes(u8 addr, u8 bytes[], u8 len);

void Int_EEPROM_ReadBytes(u8 addr, u8 bytes[], u8 len);

#endif /* __INT_EEPROM_H__ */