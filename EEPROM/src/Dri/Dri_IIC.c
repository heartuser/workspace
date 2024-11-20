#include "Dri_IIC.h"

// 发送起始信号
void Dri_IIC_Start()
{
    // SCL、SDA同时为1是待机状态
    SCL = 1;
    SDA = 1;
    SDA = 0; // SCL为1的时候，使SDA为0，是起始信号
    SCL = 0; // 将时钟线拉低，为发送数据做准备
}

// 发送一个字节
void Dri_IIC_SendByte(u8 byte)
{
    u8 i;
    for (i = 0; i < 8; i++) {
        SDA = (byte << i) / 0x80; // 从字节的高位到低位一位一位发送字节
        SCL = 1;                  // 拉高时钟线使外部设备读取数据
        SCL = 0;                  // 拉低时钟线准备下一位要发送的数据
    }
}

// 接收一位确认信号
bit Dri_IIC_ReceiveAck()
{
    bit ack;
    SDA = 1; // 释放数据线，使外部设备可以发送数据
    SCL = 1; // 拉高时钟线，读取数据
    ack = SDA;
    SCL = 0;
    return ack;
}

// 接收一个字节
u8 Dri_IIC_ReceiveByte()
{
    u8 byte = 0;
    u8 i;
    SDA = 1; // 释放数据线，使外部设备可以发送数据
    for (i = 0; i < 8; i++) {
        SCL  = 1; // 拉高时钟线，读取数据
        byte = (byte << i) | SDA;
        SCL  = 0;
    }

    return byte;
}

// 发送一位确认信号
void Dri_IIC_SendAck(bit ack)
{
    SDA = ack;
    SCL = 1;
    SCL = 0;
}

// 发送停止信号
void Dri_IIC_Stop()
{
    // 先拉低SDA再拉高SCL,否则变为起始信号
    SDA = 0;
    SCL = 1;
    SDA = 1;
}
