#include "Dri_Timer0.h"
#include <STC89C5xRC.H>

void led_Blink()
{
    static int i = 0;
    if (i == 200) {
        P00 = ~P00;
        i   = 0;
    }
    i++;
}

void main()
{
    Dri_Timer0_Init();
    Dri_Timer0_RegisterCallBack(&led_Blink);
    while (1);
}
