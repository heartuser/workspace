#include "stm32f10x.h"                  // Device header

void IC_Init()
{
    // 开启时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    // 配置输出引脚
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    // 配置定时器时钟源
    TIM_InternalClockConfig(TIM3);
    
    // 配置时基单元
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct.TIM_Period = 65536 - 1;
    TIM_TimeBaseInitStruct.TIM_Prescaler = 72 - 1;// 采样频率1M
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
    
    // 配置输入捕获
    TIM_ICInitTypeDef TIM_ICInitStruct;
    TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;// 通道1
    TIM_ICInitStruct.TIM_ICFilter = 0xF;// 滤波
    TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;// 上升沿触发
    TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;// 分频器
    TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;// 直通
    TIM_ICInit(TIM3, &TIM_ICInitStruct);
    
    // 触发源选择
    TIM_SelectInputTrigger(TIM3, TIM_TS_TI1FP1);
    
    // 选择从模式
    TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);
    
    // 开启计数
    TIM_Cmd(TIM3, ENABLE);
}

uint16_t IC_GetFreq()
{
    return 1000000 / (TIM_GetCapture1(TIM3) + 1);
}
