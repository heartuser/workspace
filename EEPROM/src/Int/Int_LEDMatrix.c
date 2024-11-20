#include "Int_LEDMatrix.h"
#include "Dri_Timer0.h"

static u8 pic_temp[8];

void Int_LEDMatrix_RefreshByTimer0()
{
    static u8 i = 0;
    P0          = 0xFF;
    // 设置显示行
    if (i == 0) {
        SER = 1;
    } else {
        SER = 0;
    }
    SCK = 0;
    SCK = 1;
    RCK = 0;
    RCK = 1;
    // 设置显示内容
    P0 = ~pic_temp[i];

    i++;
    if (i == 8) {
        i = 0;
    }
}

void Int_LEDMatrix_Init()
{
    MATRIX_LED_EN = 0; // 开启点阵LED
    P34           = 0;

    Dri_Timer0_RegisterCallBack(Int_LEDMatrix_RefreshByTimer0);
}

void Int_LEDMatrix_SetPic(u8 *pic)
{
    u8 i;
    for (i = 0; i < 8; i++) {
        pic_temp[i] = pic[i];
    }
}

void Int_LEDMatrix_Shift(u8 pic)
{
    u8 i;
    for (i = 7; i > 0; i--) {
        pic_temp[i] = pic_temp[i - 1];
    }
    pic_temp[0] = pic;
}