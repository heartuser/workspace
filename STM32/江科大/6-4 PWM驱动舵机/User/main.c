#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Servo.h"
#include "Key.h"

float angle = 0;
uint8_t keyNum;

int main(void)
{
    OLED_Init();
    OLED_Clear();
    Servo_Init();
    KEY_Init();
    OLED_ShowString(1,1,"Angle:");
    while(1)
    {
        if (Key_getNum())
        {
            angle += 30;
            if (angle > 180)
            {
                angle = 0;
            }
        }
        Servo_setAngle(angle);
        OLED_ShowNum(1,7,angle,3);
    }
}
