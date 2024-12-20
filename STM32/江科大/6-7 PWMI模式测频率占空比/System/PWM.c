#include "stm32f10x.h"                  // Device header
#include "PWM.h"

void PWM_Init(void)
{
    // 开启时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    // 配置输出引脚
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    // 配置定时器时钟源
    TIM_InternalClockConfig(TIM2);
    
    // 配置时基单元
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct.TIM_Period = 100 - 1;
    TIM_TimeBaseInitStruct.TIM_Prescaler = 1 - 1;
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
    
    // 配置PWM输出
    TIM_OCInitTypeDef TIM_OCInitStruct;
    TIM_OCStructInit(&TIM_OCInitStruct);
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStruct.TIM_Pulse = 0;
    TIM_OC1Init(TIM2, &TIM_OCInitStruct);
    
    // 开启定时器
    TIM_Cmd(TIM2, ENABLE);
}

// 设置占空比
void PWM_SetCompare1(uint16_t compare)
{
    TIM_SetCompare1(TIM2, compare);
}

// 设置频率
void PWM_SetPrescaler(uint16_t prescaler)
{
    TIM_PrescalerConfig(TIM2, prescaler, TIM_PSCReloadMode_Update);
}
