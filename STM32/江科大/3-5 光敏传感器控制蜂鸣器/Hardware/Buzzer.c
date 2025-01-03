#include "stm32f10x.h"                  // Device header
#include "Buzzer.h"

#define buzzer GPIO_Pin_12

void BUZZER_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Pin = buzzer;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;

    GPIO_Init(GPIOB, &GPIO_InitStruct);
}

// 蜂鸣器响
void BUZZER_ON(void)
{
    GPIO_ResetBits(GPIOB, buzzer);
}

// 蜂鸣器不响
void BUZZER_OFF(void)
{
    GPIO_SetBits(GPIOB, buzzer);
}

// 蜂鸣器切换响和不响
void BUZZER_Turn(void)
{
    if (GPIO_ReadOutputDataBit(GPIOB, buzzer) == 0)
    {
        GPIO_SetBits(GPIOB, buzzer);
    }
    else
    {
        GPIO_ResetBits(GPIOB, buzzer);
    }
}
