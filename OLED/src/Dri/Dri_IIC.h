#ifndef __DRI_IIC_H__
#define __DRI_IIC_H__

#include "Com_Util.h"
#include <STC89C5xRC.H>

#define SCL P17
#define SDA P16

void Dri_IIC_Start();// 发送起始信号
void Dri_IIC_SendByte(u8 byte);// 发送一个字节
bit Dri_IIC_ReceiveAck();// 接收一位确认信号
u8 Dri_IIC_ReceiveByte();// 接收一个字节
void Dri_IIC_SendAck(bit ack);// 发送一位确认信号
void Dri_IIC_Stop();// 发送停止信号


#endif /* __DRI_IIC_H__ */