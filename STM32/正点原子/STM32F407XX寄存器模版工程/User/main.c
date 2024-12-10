#include "stm32f4xx.h"

int main()
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
    
    GPIO_Init(GPIOF, &GPIO_InitStruct);
    
    //GPIO_SetBits(GPIOF,GPIO_Pin_10);
    GPIO_ResetBits(GPIOF,GPIO_Pin_10);
    while(1){
    
    }
}
