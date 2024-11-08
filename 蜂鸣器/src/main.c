#include "Int_matrixSwitch.h"
#include "Int_DigitalTube.h"
#include "Int_Buzzer.h"

/*
    ���°�������ʾ��Ӧ�İ������
*/

void main()
{
    u8 switchNum;
    Int_DigitalTube_Init();
    while (1) {
        switchNum = witchSwitchPressed(); // ��ȡ�����°����ı�ţ����û�а��������£���õ�0
        // �����������ʾ����
        if (switchNum) {                           // ����а��������£��ı�Ҫ��ʾ������
            Int_Buzzer_Note(switchNum); // ���������
            Int_DigitalTube_DisplayNum(switchNum);
        }
        Int_DigitalTube_Refresh(); // ��ʾ����
    }
}