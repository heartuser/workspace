#include "stm32f10x.h"                  // Device header
#include "LightSensor.h"

#define lightSensor GPIO_Pin_13

void LightSensor_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Pin = lightSensor;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    
    GPIO_Init(GPIOB, &GPIO_InitStruct);
}

uint8_t LightSensor_GET(void)
{
    return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13);
}

