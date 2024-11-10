#include <STC89C5xRC.H>
#include "Com_Util.h"

void INT0_Init()
{
    // 开启中断总开关
    EA = 1;
    // 开启0号1号外部中断
    EX0 = 1;
    EX1 = 1;
    // 设置0号、号外部中断为下降沿触发
    IT0 = 1;
    IT1 = 1;
    // 设置1号外部中断优先级为1.1（最高级），0号外部中断没设置优先级默认为最低级（0.0）
    IPH = 0X02;
    PX1 = 1;
}

// 外部中断0优先级比外部中断1低，按下sw3后LED1闪烁，闪烁的同时按sw4仍可切换LED2的亮灭
void main()
{   
    INT0_Init();
    while (1) {
    }
}

// 0号外部中断的服务程序
void INT0_Handler() interrupt 0
{
    Com_Util_Delay1ms(15);
    while (1)
    {
        P20 = ~P20;
        Com_Util_Delay1ms(500);
    }
    
}

// 1号外部中断的服务程序
void INT1_Handler() interrupt 2
{
    Com_Util_Delay1ms(15);
    if (P33 == 0){
        P21 = ~P21;
    }
}