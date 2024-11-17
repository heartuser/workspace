#include "Dri_UART.h"
#include <STC89C5xRC.H>
#include "Com_Util.h"
#include "Dri_Timer0.h"

static bit s_is_sending  = 0; // 0表示未在发送，1表示已在发送
static char s_buffer[16] = 0;
static u8 s_index        = 0;
static u8 s_idle_count   = 0; // 1ms加1
static bit s_is_complete = 0; // 是否接受完成标志 0：没接收完，1：接收完成

void Dri_UART_Timer0CallBack()
{
    s_idle_count++;
    if (s_index > 0 && s_idle_count > 10) { // 说明接收完成
        s_is_complete = 1;
    }
}

void Dri_UART_Init()
{
    // 1.串口的工作模式
    SM0 = 0;
    SM1 = 1;

    // 2.波特率(9600)
    // 2.1 SMOD
    PCON &= 0X7F; // SMOD = 0
    // 2.2 定时器1的配置
    // 2.2.1 定时器1的工作模式
    TMOD &= 0x0F;
    TMOD |= 0X2F;
    // 2.2.2 设置定时器1的初始值
    TH1 = 253;
    TH1 = 253;
    // 2.2.3 开启定时器
    TR1 = 1;

    // 3.串口接收配置
    REN = 1; // 接受使能
    SM2 = 0; // 是否检查结束位，0为不检查

    // 4.串口中断配置
    EA = 1; // 中断总开关
    ES = 1; // 串口中断开关
    RI = 0; // 接收中断标志位
    TI = 0; // 发送中断标志位

    // 5.向Timer0注册接受数据计数回调函数
    Dri_Timer0_RegisterCallBack(Dri_UART_Timer0CallBack);
}

// 发送单个字符
void Dri_UART_SendChar(char c)
{
    while (s_is_sending == 1);
    s_is_sending = 1;
    SBUF         = c;
}

// 发送字符串
void Dri_UART_SendStr(char *str)
{
    while (*str != 0) {
        Dri_UART_SendChar(*str);
        str++;
    }
}

// 接收字符串
bit Dri_UART_RecevieStr(char *str)
{
    if (s_is_complete == 1) {
        u8 i;
        for (i = 0; i < s_index; i++) {
            str[i] = s_buffer[i];
        }
        str[i]        = '\0';
        s_is_complete = 0;
        s_index       = 0;
        return 1;
    }
    return 0;
}

void Dri_UART_Handler() interrupt 4
{
    // 处理接收数据
    if (RI == 1) {
        s_buffer[s_index++] = SBUF;
        s_idle_count        = 0;
        RI                  = 0;
    }

    // 处理发送数据
    if (TI == 1) {
        s_is_sending = 0;
        TI           = 0;
    }
}