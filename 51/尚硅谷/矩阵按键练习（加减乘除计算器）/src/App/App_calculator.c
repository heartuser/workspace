#include "App_calculator.h"

/*
    加减乘除计算器
    按键编号对应的功能为：
    sw5    sw6    sw7    sw8            \   7   8   9   +
    sw9    sw10   sw11   sw12   ———————— \  4   5   6   -
    sw13   sw14   sw15   sw16   ———————— /  1   2   3   *
    sw17   sw18   sw19   sw20           /   0   .   =   /
*/

static u8 operflag        = 0;   // 标志输入的操作符，0表示没输入操作符，1234分别代表加减乘除
static u8 isInputOpint    = 0;   // 标志是否输入了小数点,1为输入了小数点，0为没输入
static double coefficient = 0.1; // 输入小数点后每输入一个数字，要乘以一个系数再进行操作，系数每次自身乘以0.1

// 判断当前按下的按键是否为数字,如果是返回代表的数字，否则返回10
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
    判断是否按下了操作符，如果是返回操作数标志并设置按下等号时执行的操作，否返回0
    1是加，2是减，3是乘，4是除
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
// 根据操作数和操作符，计算结果并返回，如果没有输入操作符就返回num1的值
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
    // 计算完结果后吧操作符标志和小数点置为默认值
        operflag = isInputOpint = 0;
        coefficient             = 0.1;

    return result;
}

// 根据输入的数字构建操作数
double buildNumber(double temp, u8 sigleNum)
{
    if (isInputOpint == 0) { // 未输入小数点
        temp = temp * 10 + sigleNum;
    } else { // 输入了小数点
        temp = temp + sigleNum * coefficient;
        coefficient *= 0.1;
    }

    return temp;
}