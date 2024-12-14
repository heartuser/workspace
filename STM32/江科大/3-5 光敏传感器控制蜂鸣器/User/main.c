#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Buzzer.h"
#include "LightSensor.h"

int main(void)
{
    BUZZER_Init();

    while(1)
    {
        if(LightSensor_GET() == 1)
        {
            BUZZER_ON();
        }
        else
        {
            BUZZER_OFF();
        }
    }
}
