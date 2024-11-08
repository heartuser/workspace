#include "Int_Buzzer.h"

// 以500赫兹响0.1s,延时控制频率，循环次数控制时间
void Int_Buzzer_Buzz(double frequency, double second)
{
    int i;          // 在函数开始处声明局部变量
    int num_buzzes; // 声明一个临时变量 num_buzzes 来保存需要执行的次数
    u16 delayTime;

    num_buzzes = (int)(frequency * second); // 计算需要的 buzz 次数
    delayTime  = (u16)(100000 / frequency);   // 计算延时时间

    for (i = 0; i < num_buzzes; i++) {
        P46 = ~P46;
        Com_Util_Delay10us(delayTime);
    }
}

/*
C4 (中央C) - 261.63 Hz
D4 - 293.66 Hz
E4 - 329.63 Hz
F4 - 349.23 Hz
G4 - 392.00 Hz
A4 - 440.00 Hz
B4 - 493.88 Hz
这些频率是在标准的十
*/

void Int_Buzzer_Note(u8 switchNum){
    switch (switchNum)
    {
    case 5:
        Int_Buzzer_Buzz(261.63, 0.5);
        break;
    case 6:
        Int_Buzzer_Buzz(293.66, 0.5);
        break;
    case 7:
        Int_Buzzer_Buzz(329.63, 0.5);
        break;
    case 8:
        Int_Buzzer_Buzz(349.23, 0.5);
        break;
    case 9:
        Int_Buzzer_Buzz(392.00, 0.5);
        break;
    case 10:
        Int_Buzzer_Buzz(440.00, 0.5);
        break;
    case 11:
        Int_Buzzer_Buzz(493.88, 0.5);
        break;
    
    default:
        Int_Buzzer_Buzz(1000, 0.1);
        break;
    }
}