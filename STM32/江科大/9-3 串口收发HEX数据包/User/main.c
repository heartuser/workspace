#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include "Key.h"

uint8_t RxData;
uint8_t KeyNum;

int main(void)
{
    OLED_Init();
    Serial_Init();
    KEY_Init();
    
    OLED_ShowString(1,1,"TxPacket:");
    OLED_ShowString(3,1,"RxPacket:");
    
    Serial_TxPacket[0] = 0x01;
    Serial_TxPacket[1] = 0x02;
    Serial_TxPacket[2] = 0x03;
    Serial_TxPacket[3] = 0x04;
    
    while(1)
    {
        KeyNum = Key_getNum();
        if (KeyNum == 1)
        {
            Serial_TxPacket[0]++;
            Serial_TxPacket[1]++;
            Serial_TxPacket[2]++;
            Serial_TxPacket[3]++;
            
            Serial_SendPacket();
            
            OLED_ShowHexNum(2,1,Serial_TxPacket[0],2);
            OLED_ShowHexNum(2,5,Serial_TxPacket[1],2);
            OLED_ShowHexNum(2,9,Serial_TxPacket[2],2);
            OLED_ShowHexNum(2,13,Serial_TxPacket[3],2);
        }
        
        
        if (Serial_GetRxFlag() == 1)
        {
            OLED_ShowHexNum(4,1,Serial_RxPacket[0],2);
            OLED_ShowHexNum(4,5,Serial_RxPacket[1],2);
            OLED_ShowHexNum(4,9,Serial_RxPacket[2],2);
            OLED_ShowHexNum(4,13,Serial_RxPacket[3],2);
            
        }
    }
}
