#include <Int_Key.h>

#define LED1 P20
#define LED2 P21
#define LED3 P22
#define LED4 P23

void main()
{

    while (1)
    {
        if(Int_Key_IsSW1Pressed()){
            LED1 = ~LED1;
        }
        if(Int_Key_IsSW2Pressed()){
            LED2 = ~LED2;
        }
        if(Int_Key_IsSW3Pressed()){
            LED3 = ~LED3;
        }
        if(Int_Key_IsSW4Pressed()){
            LED4 = ~LED4;
        }
    }
    
}