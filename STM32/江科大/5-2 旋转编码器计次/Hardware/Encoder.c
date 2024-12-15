#include "stm32f10x.h"                  // Device header
#include "Encoder.h"

int16_t encoder_count;

void Encoder_Init(void)
{
    // 开启GPIO和AFIO的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
    
    // 配置GPIO(B0/B1)
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    
    // 配置AFIO
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);
    
    // 配置EXTI
    EXTI_InitTypeDef EXTI_InitStruct;
    EXTI_InitStruct.EXTI_Line = EXTI_Line0;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
    
    EXTI_Init(&EXTI_InitStruct);
    
    // 配置NVIC
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
    
    NVIC_Init(&NVIC_InitStruct);
}

void EXTI0_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line0) == SET)
    {
        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 1)
        {
            encoder_count++;
        }
        else
        {
            encoder_count--;
        }
    }
    
    EXTI_ClearITPendingBit(EXTI_Line0);
}

int16_t Encoder_GET(void)
{
    return encoder_count;
}
