#include "Dri_IIC.h"

// ������ʼ�ź�
void Dri_IIC_Start()
{
    // SCL��SDAͬʱΪ1�Ǵ���״̬
    SCL = 1;
    SDA = 1;
    SDA = 0; // SCLΪ1��ʱ��ʹSDAΪ0������ʼ�ź�
    SCL = 0; // ��ʱ�������ͣ�Ϊ����������׼��
}

// ����һ���ֽ�
void Dri_IIC_SendByte(u8 byte)
{
    u8 i;
    for (i = 0; i < 8; i++) {
        SDA = (byte << i) / 0x80; // ���ֽڵĸ�λ����λһλһλ�����ֽ�
        SCL = 1;                  // ����ʱ����ʹ�ⲿ�豸��ȡ����
        SCL = 0;                  // ����ʱ����׼����һλҪ���͵�����
    }
}

// ����һλȷ���ź�
bit Dri_IIC_ReceiveAck()
{
    bit ack;
    SDA = 1; // �ͷ������ߣ�ʹ�ⲿ�豸���Է�������
    SCL = 1; // ����ʱ���ߣ���ȡ����
    ack = SDA;
    SCL = 0;
    return ack;
}

// ����һ���ֽ�
u8 Dri_IIC_ReceiveByte()
{
    u8 byte = 0;
    u8 i;
    SDA = 1; // �ͷ������ߣ�ʹ�ⲿ�豸���Է�������
    for (i = 0; i < 8; i++) {
        SCL  = 1; // ����ʱ���ߣ���ȡ����
        byte = (byte << i) | SDA;
        SCL  = 0;
    }

    return byte;
}

// ����һλȷ���ź�
void Dri_IIC_SendAck(bit ack)
{
    SDA = ack;
    SCL = 1;
    SCL = 0;
}

// ����ֹͣ�ź�
void Dri_IIC_Stop()
{
    // ������SDA������SCL,�����Ϊ��ʼ�ź�
    SDA = 0;
    SCL = 1;
    SDA = 1;
}
