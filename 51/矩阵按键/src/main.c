#include "Int_matrixSwitch.h"
#include "Int_DigitalTube.h"

/*
    按下按键，显示对应的按键编号
*/

void main()
{
    u8 switchNum;
    Int_DigitalTube_Init();
    while (1)
    {
        switchNum = witchSwitchPressed();// 获取被按下按键的编号，如果没有按键被按下，则得到0
        //在数码管上显示数字
        if (switchNum){// 如果有按键被按下，改变要显示的数字
            Int_DigitalTube_DisplayNum(switchNum);
        }
        Int_DigitalTube_Refresh();// 显示数字
    }
    
}