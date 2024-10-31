#include "Int_DigitalTube.h"
#include <STC89C5xRC.H>

// 数字0-9的编码
static u8 s_codes[10] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F  // 9
};

static s_buffer[8];

// 初始化，开启数码管关闭LED，尚硅谷开发板专用，普中开发板不需要
void Int_DigitalTube_Init()
{
    SMG_EN = 0;
    LED_EN = 0;
}

/**
 * @brief 内部方法，让数码管某一位显示特定数字
 *
 * @param position 片选, 从左到右[0-7]
 * @param num_code 显示想要的数字编码
 */
static void Int_DigitalTube_DisplaySingle(u8 position, u8 num_code)
{
    P0 = 0x00;
    // 位选：P15 P14 P13(尚硅谷)  P22~P24(普中)
    P2 = position << 2;
    // P2 &= 0xC7;
    // P2 |= position;

    // 段选：P0
    P0 = num_code;
}

/**
 * @brief 设置显存数组
 *
 * @param num 待展示数字
 */
void Int_DigitalTube_DisplayNum(u32 num)
{
    u8 i;
    for (i = 0; i < 8; i++) {
        s_buffer[i] = 0x00; //当前位置灯全部熄灭
    }

    if (num == 0) {
        s_buffer[7] = s_codes[0];
        return;
    }

    i = 0;
    while (num > 0) {
        s_buffer[i] = s_codes[num % 10];
        num /= 10;
        i++;
    }
}

/**
 * @brief 动态扫描
 *
 */
void Int_DigitalTube_Refresh()
{
    u8 i;
    for (i = 0; i < 8; i++) {
        Int_DigitalTube_DisplaySingle(i, s_buffer[i]);
        Com_Util_Delay1ms(1);
    }
}
