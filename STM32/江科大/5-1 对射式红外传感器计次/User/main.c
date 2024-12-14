#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "CountSensor.h"

uint8_t keyNum;

int main(void)
{
    OLED_Init();
    CountSensor_Init();
    OLED_Clear();
    OLED_ShowString(1, 1, "Count:");
    while(1)
    {
        OLED_ShowNum(1, 7, CountSensor_GET(), 5);
    }
}
