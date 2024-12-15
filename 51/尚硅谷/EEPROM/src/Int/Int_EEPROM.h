#ifndef __INT_EEPROM_H__
#define __INT_EEPROM_H__

#include "Com_Util.h"

/**
 * @brief д��һ���ֽ�
 * 
 * @param addr д�����ʼ��ַ
 * @param byte Ҫд����ֽ�����
 * @param len Ҫд����ֽ�����ĳ���
 */
void Int_EEPROM_WriteBytes(u8 addr, u8 bytes[], u8 len);

void Int_EEPROM_ReadBytes(u8 addr, u8 bytes[], u8 len);

#endif /* __INT_EEPROM_H__ */