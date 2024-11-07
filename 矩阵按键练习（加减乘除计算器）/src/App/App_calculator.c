#include "App_calculator.h"

/*
    �Ӽ��˳�������
    ������Ŷ�Ӧ�Ĺ���Ϊ��
    sw5    sw6    sw7    sw8            \   7   8   9   +
    sw9    sw10   sw11   sw12   ���������������� \  4   5   6   -
    sw13   sw14   sw15   sw16   ���������������� /  1   2   3   *
    sw17   sw18   sw19   sw20           /   0   .   =   /
*/

static u8 operflag        = 0;   // ��־����Ĳ�������0��ʾû�����������1234�ֱ����Ӽ��˳�
static u8 isInputOpint    = 0;   // ��־�Ƿ�������С����,1Ϊ������С���㣬0Ϊû����
static double coefficient = 0.1; // ����С�����ÿ����һ�����֣�Ҫ����һ��ϵ���ٽ��в�����ϵ��ÿ���������0.1

// �жϵ�ǰ���µİ����Ƿ�Ϊ����,����Ƿ��ش�������֣����򷵻�10
u8 isNum(u8 switchNum)
{
    u8 num;
    switch (switchNum) {
        case 5:
            num = 7;
            break;
        case 6:
            num = 8;
            break;
        case 7:
            num = 9;
            break;
        case 9:
            num = 4;
            break;
        case 10:
            num = 5;
            break;
        case 11:
            num = 6;
            break;
        case 13:
            num = 1;
            break;
        case 14:
            num = 2;
            break;
        case 15:
            num = 3;
            break;
        case 17:
            num = 0;
            break;
        default:
            num = 10;
    }
    return num;
}

/*
    �ж��Ƿ����˲�����������Ƿ��ز�������־�����ð��µȺ�ʱִ�еĲ������񷵻�0
    1�Ǽӣ�2�Ǽ���3�ǳˣ�4�ǳ�
*/
u8 pressedOperator(u8 switchNum)
{
    switch (switchNum) {
        case 8:
            operflag = 1;
            return 1;
        case 12:
            operflag = 2;
            return 1;
        case 16:
            operflag = 3;
            return 1;
        case 20:
            operflag = 4;
            return 1;
        default:
            return 0;
    }
}
void inputPoint()
{
    isInputOpint = 1;
}
// ���ݲ������Ͳ������������������أ����û������������ͷ���num1��ֵ
double getResult(double num1, double num2)
{
    double result = 0;
    if (operflag == 0) {
        result = num1;
    } else {
        switch (operflag) {
            case 1:
                result = num1 + num2;
                break;
            case 2:
                result = num1 - num2;
                break;
            case 3:
                result = num1 * num2;
                break;
            case 4:
                result = num1 / num2;
                break;
        }
        
    }
    // ����������ɲ�������־��С������ΪĬ��ֵ
        operflag = isInputOpint = 0;
        coefficient             = 0.1;

    return result;
}

// ������������ֹ���������
double buildNumber(double temp, u8 sigleNum)
{
    if (isInputOpint == 0) { // δ����С����
        temp = temp * 10 + sigleNum;
    } else { // ������С����
        temp = temp + sigleNum * coefficient;
        coefficient *= 0.1;
    }

    return temp;
}