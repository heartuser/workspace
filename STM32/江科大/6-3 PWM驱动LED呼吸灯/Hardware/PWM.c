#include "stm32f10x.h"                  // Device header
#include "PWM.h"

void PWM_Init(void)
{
    // 开启时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    // A0重映射到A15
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); // 开启AFIO的时钟
    GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE); // 将输出重映射到A15
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);// A15端口原来被调试端口占用，解除占用
    
    // 配置引脚模式
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;// 配置为复用推挽输出，信号来自片上外设
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    // 为定时器TIM2选择时钟源
    TIM_InternalClockConfig(TIM2);
    
    // 配置时基单元
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct.TIM_Period = 100 - 1;     // ARR
    TIM_TimeBaseInitStruct.TIM_Prescaler = 720 - 1;  // PSC
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
    
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
    
    // 配置输出比较单元
    TIM_OCInitTypeDef TIM_OCInitStruct;
    TIM_OCStructInit(&TIM_OCInitStruct);
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_Pulse = 50;      // CCR
    TIM_OC1Init(TIM2, &TIM_OCInitStruct);
    
    TIM_Cmd(TIM2, ENABLE);
}
