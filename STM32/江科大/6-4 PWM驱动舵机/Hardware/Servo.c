#include "stm32f10x.h"                  // Device header 
#include "PWM.h"

void Servo_Init(void)
{
    PWM_Init();
}

// 设置舵机角度（0°-180°）
void Servo_setAngle(float angle)
{
    TIM_SetCompare2(TIM2, (0.5 + (2.0 / 180) * angle) * 1000);
}

