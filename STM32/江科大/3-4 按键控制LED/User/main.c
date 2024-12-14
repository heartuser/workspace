#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"

uint8_t keyNum;

int main(void)
{
    LED_Init();
    KEY_Init();
    
    while(1)
    {
        keyNum = Key_getNum();
        if (keyNum == 1)
        {
            LED1_Turn();
        }
        if (keyNum == 2)
        {
            LED2_Turn();
        }
    }
}
