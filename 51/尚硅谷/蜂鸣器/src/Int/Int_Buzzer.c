#include "Int_Buzzer.h"

// ��500������0.1s,��ʱ����Ƶ�ʣ�ѭ����������ʱ��
void Int_Buzzer_Buzz(double frequency, double second)
{
    int i;          // �ں�����ʼ�������ֲ�����
    int num_buzzes; // ����һ����ʱ���� num_buzzes ��������Ҫִ�еĴ���
    u16 delayTime;

    num_buzzes = (int)(frequency * second); // ������Ҫ�� buzz ����
    delayTime  = (u16)(100000 / frequency);   // ������ʱʱ��

    for (i = 0; i < num_buzzes; i++) {
        P46 = ~P46;
        Com_Util_Delay10us(delayTime);
    }
}

/*
C4 (����C) - 261.63 Hz
D4 - 293.66 Hz
E4 - 329.63 Hz
F4 - 349.23 Hz
G4 - 392.00 Hz
A4 - 440.00 Hz
B4 - 493.88 Hz
��ЩƵ�����ڱ�׼��ʮ
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