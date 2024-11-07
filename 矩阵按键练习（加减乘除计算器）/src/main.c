#include "Int_matrixSwitch.h"
#include "Int_DigitalTube.h"
#include "App_calculator.h"

/*
    �Ӽ��˳�������
    ������Ŷ�Ӧ�Ĺ���Ϊ��
    sw5    sw6    sw7    sw8            \   7   8   9   +
    sw9    sw10   sw11   sw12   ���������������� \  4   5   6   -
    sw13   sw14   sw15   sw16   ���������������� /  1   2   3   *
    sw17   sw18   sw19   sw20           /   0   .   =   /
*/

void main()
{
    u8 switchNum, sigleNum, isOper;  // ������ţ��������������,�Ƿ������˲�����
    double num1, num2, temp, result, displayNum; // ������������,temp������װ������,�����ʵʱ��ʾdisplayNum��ֵ,result������
    num1 = num2 = isOper = 0;        // ��ʼ��
    sigleNum             = 10;       // ֵ��0-9�ĸ�λ����10˵��û�����ְ���������
    Int_DigitalTube_Init();          // �����������ʾ���ر�LED
    while (1) {
        switchNum = witchSwitchPressed(); // ��ȡ�����°����ı�ţ����û�а��������£���õ�0
        // �����������ʾ����
        if (switchNum) {                                // ����а��������£��ı�Ҫ��ʾ������
            if (isNum(switchNum) != 10) {               // �жϰ��µİ����Ƿ�Ϊ����
                sigleNum = isNum(switchNum);            // ���水�°������������
                temp     = buildNumber(temp, sigleNum); // ��װ������
                if (isOper == 0) {                      // ���û��������������ı�num1��ֵ������ı�num2��ֵ
                    num1 = temp;
                } else {
                    num2 = temp;
                }
                displayNum = temp;
            } else if (pressedOperator(switchNum)) { // �ж��Ƿ����˲�����
                isOper = 1;
                temp = 0;
            } else if (switchNum == 18) { // �ж��Ƿ�����С����
                inputPoint();
            } else if (switchNum == 19) { // �ж��Ƿ����˵��ں�
                result = getResult(num1, num2);
                displayNum = result;
                temp = 0;
                isOper = 0;
                //Int_DigitalTube_DisplayNum(result); // ��ʾ���
            }
            Int_DigitalTube_DisplayNum(displayNum); // �������д��Ҫ��ʾ������
        }
        Int_DigitalTube_Refresh(); // ��ʾ����
    }
}