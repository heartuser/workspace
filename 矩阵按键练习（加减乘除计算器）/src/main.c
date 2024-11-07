#include "Int_matrixSwitch.h"
#include "Int_DigitalTube.h"
#include "App_calculator.h"

/*
    加减乘除计算器
    按键编号对应的功能为：
    sw5    sw6    sw7    sw8            \   7   8   9   +
    sw9    sw10   sw11   sw12   ———————— \  4   5   6   -
    sw13   sw14   sw15   sw16   ———————— /  1   2   3   *
    sw17   sw18   sw19   sw20           /   0   .   =   /
*/

void main()
{
    u8 switchNum, sigleNum, isOper;  // 按键编号，按键代表的数字,是否输入了操作符
    double num1, num2, temp, result, displayNum; // 两个被操作数,temp用来组装操作数,数码管实时显示displayNum的值,result保存结果
    num1 = num2 = isOper = 0;        // 初始化
    sigleNum             = 10;       // 值是0-9的个位数，10说明没有数字按键被按下
    Int_DigitalTube_Init();          // 开启数码管显示，关闭LED
    while (1) {
        switchNum = witchSwitchPressed(); // 获取被按下按键的编号，如果没有按键被按下，则得到0
        // 在数码管上显示数字
        if (switchNum) {                                // 如果有按键被按下，改变要显示的数字
            if (isNum(switchNum) != 10) {               // 判断按下的按键是否为数字
                sigleNum = isNum(switchNum);            // 保存按下按键代表的数字
                temp     = buildNumber(temp, sigleNum); // 组装操作数
                if (isOper == 0) {                      // 如果没有输入操作符，改变num1的值，否则改变num2的值
                    num1 = temp;
                } else {
                    num2 = temp;
                }
                displayNum = temp;
            } else if (pressedOperator(switchNum)) { // 判断是否按下了操作符
                isOper = 1;
                temp = 0;
            } else if (switchNum == 18) { // 判断是否按下了小数点
                inputPoint();
            } else if (switchNum == 19) { // 判断是否按下了等于号
                result = getResult(num1, num2);
                displayNum = result;
                temp = 0;
                isOper = 0;
                //Int_DigitalTube_DisplayNum(result); // 显示结果
            }
            Int_DigitalTube_DisplayNum(displayNum); // 向数码管写入要显示的数字
        }
        Int_DigitalTube_Refresh(); // 显示数字
    }
}