#include "Int_matrixSwitch.h"
#include "Int_DigitalTube.h"

void main()
{
    u8 switchNum;
    Int_DigitalTube_Init();
    while (1)
    {
        switchNum = witchSwitchPressed();
        //�����������ʾ����
        if (switchNum){
            Int_DigitalTube_DisplayNum(switchNum);
        }
        Int_DigitalTube_Refresh();
    }
    
}