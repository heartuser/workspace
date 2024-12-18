#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"

int16_t compare = 1;
uint16_t flag;

int main(void)
{
    OLED_Init();
    OLED_Clear();
    PWM_Init();
    while(1)
    {
        OLED_ShowSignedNum(1,1,compare,3);
        
        if (compare > 100 || compare < 1)
        {
            flag++;
        }
        if (flag % 2 == 0)
        {
            TIM_SetCompare1(TIM2, compare++);
        }
        else
        {
            TIM_SetCompare1(TIM2, compare--);
        }
        Delay_ms(10);
    }
}
