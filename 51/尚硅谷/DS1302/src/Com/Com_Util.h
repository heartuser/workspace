#ifndef _COM_UTIL_H_
#define _COM_UTIL_H_

typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;

void Com_Util_Delay1ms(u16 count);

void Com_Util_Delay480us(void);
void Com_Util_Delay60us(void);
void Com_Util_Delay420us(void);
void Com_Util_Delay10us(void);
void Com_Util_Delay50us(void);

#endif // !_COM_UTIL_H_