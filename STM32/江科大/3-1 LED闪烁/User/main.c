#include "stm32f10x.h"                  // Device header
#include "Delay.h"

int main(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    
    GPIO_Init(GPIOA,&GPIO_InitStruct);
    
    while(1){
//        GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);
//        Delay_ms(1000);
//        GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_SET);
//        Delay_ms(1000);
//        
//        GPIO_SetBits(GPIOA,GPIO_Pin_0);
//        Delay_ms(1000);
//        GPIO_ResetBits(GPIOA,GPIO_Pin_0);
//        Delay_ms(1000);
        
        GPIO_WriteBit(GPIOA,GPIO_Pin_0,(BitAction)1);
        Delay_ms(1000);
        GPIO_WriteBit(GPIOA,GPIO_Pin_0,(BitAction)0);
        Delay_ms(1000);
    }
}
