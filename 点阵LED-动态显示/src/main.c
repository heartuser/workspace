#include "Int_LEDMatrix.h"
#include "Dri_Timer0.h"

void main()
{
    u8 picture[26] = {0xF8, 0x0A, 0xEC, 0xAF, 0xEC, 0x8A, 0xF8, 0x00,
                0x10, 0xF9, 0x97, 0xF1, 0x88, 0xAA, 0xFF, 0xAA,
                0x88, 0x00, 0x14, 0x0A, 0xF5, 0x92, 0x92, 0xF5,
                0x0A, 0x14};
    Int_LEDMatrix_Init();
    Dri_Timer0_Init();
    Dri_Timer0_RegisterCallBack(Int_LEDMatrix_RefreshByTimer0);
    while (1) {
        u8 i;
        for (i = 0; i < sizeof(picture); i++)
        {
            Int_LEDMatrix_Shift(picture[i]);
            Com_Util_Delay1ms(150);
        }
    }
}