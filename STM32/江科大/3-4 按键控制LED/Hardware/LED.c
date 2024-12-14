#include "stm32f10x.h"                  // Device header
#include "LED.h"

#define led1 GPIO_Pin_7
#define led2 GPIO_Pin_6

// 初始化
void LED_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Pin = led1 | led2;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    GPIO_SetBits(GPIOA, led1 | led2);
}

void LED1_ON(void)
{
    GPIO_ResetBits(GPIOA, led1);
}

void LED1_OFF(void)
{
    GPIO_SetBits(GPIOA, led1);
}

void LED1_Turn(void)
{
    if (GPIO_ReadOutputDataBit(GPIOA, led1) == 0)
    {
        GPIO_SetBits(GPIOA, led1);
    }
    else
    {
        GPIO_ResetBits(GPIOA, led1);
    }
}

void LED2_ON(void)
{
    GPIO_ResetBits(GPIOA, led2);
}

void LED2_OFF(void)
{
    GPIO_SetBits(GPIOA, led2);
}

void LED2_Turn(void)
{
    if (GPIO_ReadOutputDataBit(GPIOA, led2) == 0)
    {
        GPIO_SetBits(GPIOA, led2);
    }
    else
    {
        GPIO_ResetBits(GPIOA, led2);
    }
}
