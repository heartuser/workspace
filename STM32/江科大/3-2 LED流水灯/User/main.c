#include "stm32f10x.h"                  // Device header
#include "Delay.h"

int main(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_All;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    int i = 0;
    int tmp1 = 0x0001;
    int tmp2 = 0x0080;
    int tmp3 = 0x0000;
    
    while(1)
    {
        //流水灯1
//        GPIO_Write(GPIOA, ~0x0001); // 0000 0000 0000 0001
//        Delay_ms(100);
//        GPIO_Write(GPIOA, ~0x0002); // 0000 0000 0000 0010
//        Delay_ms(100);
//        GPIO_Write(GPIOA, ~0x0004); // 0000 0000 0000 0100
//        Delay_ms(100);
//        GPIO_Write(GPIOA, ~0x0008); // 0000 0000 0000 1000
//        Delay_ms(100);
//        GPIO_Write(GPIOA, ~0x0010); // 0000 0000 0001 0000
//        Delay_ms(100);
//        GPIO_Write(GPIOA, ~0x0020); // 0000 0000 0010 0000
//        Delay_ms(100);
//        GPIO_Write(GPIOA, ~0x0040); // 0000 0000 0100 0000
//        Delay_ms(100);
//        GPIO_Write(GPIOA, ~0x0080); // 0000 0000 1000 0000
//        Delay_ms(100);
        
        // 流水灯2
//        for (i = 0;i < 8;i++)
//        {
//            GPIO_Write(GPIOA, ~(tmp1 << i));
//            Delay_ms(200);
//        }
        
        // 流水灯3
//        for (i = 0;i < 8;i++)
//        {
//            GPIO_Write(GPIOA, ~((tmp1 << i)|(tmp2 >> i)));
//            Delay_ms(200);
//        }

        // 流水灯4
        GPIO_Write(GPIOA, ~(tmp1 | tmp3));
        if (tmp3 % 2 == 0)
        {
            if (((tmp1 << 1) != 0x0100) && (((tmp1 << 1) & tmp3) == 0))
            {
                tmp1 <<= 1;
            }
            else
            {
                tmp3 |= tmp1;
                tmp1 = 0x0001;
            }
        }
        else
        {
            if (tmp3 == 0x00FF)
            {
                tmp1 = 0x0080;
                tmp3 = 0x007F;
                i++;
            }
            
            if (tmp1 < 0x0100)
            {
                tmp1 <<= 1;
            }
            else
            {
                tmp3 >>= 1;
                tmp1 = 0x0080 >> i;
                i++;
                if (i == 8)
                {
                    i = 0;
                    tmp1 = 0x0001;
                    tmp3 = 0x0000;
                }
            }
        }
        
        Delay_ms(100);
    }
}
