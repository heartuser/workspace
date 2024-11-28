#include "Int_OLED.h"

void main()
{

    Int_OLED_Init();
    Int_OLED_Clear();
    Int_OLED_ShowStr(0, 0, "hello world!");
    Int_OLED_ShowNum(0, 1, -123456789);
    Int_OLED_ShowStr(0, 2, "abcdefghijk");
    Int_OLED_ShowStr(0, 3, "ABCDEFGHIJK");
    while (1) {
    }
}