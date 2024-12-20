#include "Key.h"
#include "Delay.h"

#define key1 GPIO_Pin_1

void KEY_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Pin = key1;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    
    GPIO_Init(GPIOB, &GPIO_InitStruct);
}

uint8_t Key_getNum(void)
{
    uint8_t keyNum = 0;
    
    // 键1被按下
    if (GPIO_ReadInputDataBit(GPIOB, key1) == 0)
    {
        Delay_ms(10);
        if (GPIO_ReadInputDataBit(GPIOB, key1) == 0)
        {
            keyNum = 1;
        }
        while(GPIO_ReadInputDataBit(GPIOB, key1) == 0);
        Delay_ms(10);
    }
    
    return keyNum;
}
