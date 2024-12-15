#include <STC89C5xRC.H>
#include <STDIO.H>
#include "Dri_Timer0.h"
#include "Com_Util.h"

#define MAX_CALLBACK_COUNT 4

static Timer0_Callback s_callbacks[MAX_CALLBACK_COUNT];

void Dri_Timer0_Init()
{
    u8 i;
    // 打开中断总开关
    EA = 1;
    // 打开定时器0中断开关
    ET0 = 1;
    // 定时器0工作方式(GATE=0；C/T=0；M1=0，M0=1)
    TMOD &= 0xF0;
    TMOD |= 0x01;
    // 设置脉冲计数器初始值（晶振频率11.0592MHz,16位不自动重载模式，1ms）
    TL0 = 0x66;
    TH0 = 0xFC;
    // 开启定时器
    TR0 = 1;

    // 初始化函数指针数组的值
    for (i = 0; i < MAX_CALLBACK_COUNT; i++) {
        s_callbacks[i] = NULL;
    }
    
}

bit Dri_Timer0_RegisterCallBack(Timer0_Callback callBack)
{
    u8 i;
    for (i = 0; i < MAX_CALLBACK_COUNT; i++) { // 防止重复注册
        if (s_callbacks[i] == callBack) {
            return 1;
        }
    }

    for (i = 0; i < MAX_CALLBACK_COUNT; i++) { // 寻找空位进行注册
        if (s_callbacks[i] == NULL) {
            s_callbacks[i] = callBack;
            return 1;
        }
    }

    return 0; // 既不存在指定函数指针，也没有空位，注册失败
}

bit Dri_Timer0_DeregisterCallBack(Timer0_Callback callBack)
{
    u8 i;
    for (i = 0; i < MAX_CALLBACK_COUNT; i++) {
        if (s_callbacks[i] == callBack) {
            s_callbacks[i] = NULL;
            return 1;
        }
    }
    return 0;
}

// 定时器0的中断服务程序
void timer0Handler() interrupt 1
{
    u8 i;
    // 初始化计时器的值
    TL0 = 0x66;
    TH0 = 0xFC;

    for (i = 0; i < MAX_CALLBACK_COUNT; i++) {
        if (s_callbacks[i] != NULL) {
            s_callbacks[i]();
        }
    }
}