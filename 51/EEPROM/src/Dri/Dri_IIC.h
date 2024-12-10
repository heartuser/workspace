#ifndef __DRI_IIC_H__
#define __DRI_IIC_H__

#include "Com_Util.h"
#include <STC89C5xRC.H>

#define SCL P17
#define SDA P16

void Dri_IIC_Start();// ������ʼ�ź�
void Dri_IIC_SendByte(u8 byte);// ����һ���ֽ�
bit Dri_IIC_ReceiveAck();// ����һλȷ���ź�
u8 Dri_IIC_ReceiveByte();// ����һ���ֽ�
void Dri_IIC_SendAck(bit ack);// ����һλȷ���ź�
void Dri_IIC_Stop();// ����ֹͣ�ź�


#endif /* __DRI_IIC_H__ */