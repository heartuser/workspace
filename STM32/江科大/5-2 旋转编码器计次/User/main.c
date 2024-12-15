#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Encoder.h"

uint8_t keyNum;

int main(void)
{
    OLED_Init();
    OLED_Clear();
    Encoder_Init();
    OLED_ShowString(1,1,"Count:");
    while(1)
    {
        OLED_ShowSignedNum(1, 7, Encoder_GET(), 6);
    }
}
