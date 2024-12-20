#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Motor.h"
#include "Key.h"

int8_t Speed = 0;
uint8_t flag = 0;

int main(void)
{
    OLED_Init();
    OLED_Clear();
    Motor_Init();
    KEY_Init();
    OLED_ShowString(1,1,"Speed:");
    while(1)
    {
        // 按下按键速度变化20%，到+100或-100时改变变化方向
        if (Key_getNum())
        {
            if (flag % 2 == 0)
            {
                Speed += 20;
            }
            else
            {
                Speed -= 20;
            }
            if (Speed == 100 | Speed == -100)
            {
                flag++;
            }
        }
        Motor_SetSpeed(Speed);
        OLED_ShowSignedNum(1,7,Speed,3);
    }
}
