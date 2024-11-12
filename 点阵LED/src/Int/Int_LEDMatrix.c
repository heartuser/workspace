#include "Int_LEDMatrix.h"

static u8 pic_temp[8];

void Int_LEDMatrix_Init()
{
    MATRIX_LED_EN = 0; // 开启数码管
    P34 = 0;
}

void Int_LEDMatrix_SetPic(u8 *pic)
{
    u8 i;
    for (i = 0; i < 8; i++)
    {
        pic_temp[i] = pic[i];
    }
    
}

void Int_LEDMatrix_Refresh()
{
    u8 i;
    P0 = 0xFF;
    for (i = 0; i < 8; i++) {
        if (i == 0) {
            SER = 1;
        } else {
            SER = 0;
        }
        SCK = 0;
        SCK = 1;
        RCK = 0;
        RCK = 1;
        P0 = ~pic_temp[i];
        Com_Util_Delay1ms(1);
    }
}

void Int_LEDMatrix_RefreshByTimer0(){
    static u8 i = 0;
    P0 = 0xFF;
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
    if (i == 8){
        i = 0;
    }
}