#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "OLED.h"
#include "IC.h"

int main(void)
{
    OLED_Init();
    PWM_Init();
    IC_Init();
    
    OLED_ShowString(1,1,"Freq:00000Hz");
    
    PWM_SetCompare1(30);
    PWM_SetPrescaler(720 - 1);
    
    
    while(1){
        OLED_ShowNum(1,6,IC_GetFreq(),5);
    }
}
