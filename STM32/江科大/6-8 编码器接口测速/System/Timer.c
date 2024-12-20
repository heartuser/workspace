#include "stm32f10x.h"                  // Device header

extern uint16_t Num;

void Timer_Init(void)
{
    // 开启定时器2的时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    
    // 配置时钟源为内部时钟（默认为内部时钟，不配置也行）
    //TIM_InternalClockConfig(TIM2);
    
    // 配置时基单元
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct.TIM_Period = 10000 - 1;
    TIM_TimeBaseInitStruct.TIM_Prescaler = 7200 - 1;
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
    
    // 定时器初始化完之后会立即进行一次中断，手动清除一次标志位，使复位后Num从0开始
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    
    // 开启定时器中断
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    
    // 配置优先级
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // 优先级分组
    
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
    
    NVIC_Init(&NVIC_InitStruct);
    
    // 启动定时器
    TIM_Cmd(TIM2, ENABLE);
}


