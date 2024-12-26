#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MyDMA.h"

uint8_t DataA[] = {0x01,0x02,0x03,0x04};
uint8_t DataB[] = {0,0,0,0};

int main(void)
{
    OLED_Init();
    
    MyDMA_init((uint32_t)DataA, (uint32_t)DataB, 4);
    
    OLED_ShowString(1,1,"DataA");
    OLED_ShowHexNum(1,7,(uint32_t)DataA,8);
    
    OLED_ShowString(3,1,"DataB");
    OLED_ShowHexNum(3,7,(uint32_t)DataB,8);
    
    while(1)
    {
        DataA[0]++;
        DataA[1]++;
        DataA[2]++;
        DataA[3]++;
        
        OLED_ShowHexNum(2,1,DataA[0],2);
        OLED_ShowHexNum(2,5,DataA[1],2);
        OLED_ShowHexNum(2,9,DataA[2],2);
        OLED_ShowHexNum(2,13,DataA[3],2);
        
        OLED_ShowHexNum(4,1,DataB[0],2);
        OLED_ShowHexNum(4,5,DataB[1],2);
        OLED_ShowHexNum(4,9,DataB[2],2);
        OLED_ShowHexNum(4,13,DataB[3],2);
        
        Delay_s(1);
        
        My_DMA_Transfer();
        
        OLED_ShowHexNum(2,1,DataA[0],2);
        OLED_ShowHexNum(2,5,DataA[1],2);
        OLED_ShowHexNum(2,9,DataA[2],2);
        OLED_ShowHexNum(2,13,DataA[3],2);
        
        OLED_ShowHexNum(4,1,DataB[0],2);
        OLED_ShowHexNum(4,5,DataB[1],2);
        OLED_ShowHexNum(4,9,DataB[2],2);
        OLED_ShowHexNum(4,13,DataB[3],2);
        
        Delay_s(1);
        
    }
}
