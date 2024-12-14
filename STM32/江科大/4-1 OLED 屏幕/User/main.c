#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"

uint8_t keyNum;

int main(void)
{
    OLED_Init();
    OLED_Clear();
    OLED_ShowString(1,1,"helloworld!");
    OLED_ShowHexNum(2,1,16151515,8);
    OLED_ShowBinNum(3,1,1024,16);
    OLED_ShowSignedNum(4,1,-4256,5);
    while(1)
    {
        
    }
}
