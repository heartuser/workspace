#include "Int_matrixSwitch.h"

// static u8 refreshY(){
//     if (y1 == 0){
//         Com_Util_Delay1ms(15);
//         if (y1 == 0){
//             while (y1 == 0);
//             Com_Util_Delay1ms(15);
//             return 1;
//         }
//     }else if (y2 == 0){
//         Com_Util_Delay1ms(15);
//         if (y2 == 0){
//             while (y2 == 0);
//             Com_Util_Delay1ms(15);
//             return 2;
//         }
//     }else if (y3 == 0){
//         Com_Util_Delay1ms(15);
//         if (y3 == 0){
//             while (y3 == 0);
//             Com_Util_Delay1ms(15);
//             return 3;
//         }
//     }else if (y4 == 0){
//         Com_Util_Delay1ms(15);
//         if (y4 == 0){
//             while (y4 == 0);
//             Com_Util_Delay1ms(15);
//             return 4;
//         }
//     }
//     return 5;
// }

// u8 witchSwitchPressed()
// {
//     u8 switchNum = 0;
//     u8 ySwitchNum;
//     while (1)
//     {
//         x1 = 0;
//         ySwitchNum = refreshY();
//         if (ySwitchNum != 5){
//             switchNum = 0 * 4 + ySwitchNum;
//             return switchNum;
//         }
//         x1 = 1;

//         x2 = 0;
//         ySwitchNum = refreshY();
//         if (ySwitchNum != 5){
//             switchNum = 1 * 4 + ySwitchNum;
//             return switchNum;
//         }
//         x2 = 1;

//         x3 = 0;
//         ySwitchNum = refreshY();
//         if (ySwitchNum != 5){
//             switchNum = 2 * 4 + ySwitchNum;
//             return switchNum;
//         }
//         x3 = 1;

//         x4 = 0;
//         ySwitchNum = refreshY();
//         if (ySwitchNum != 5){
//             switchNum = 3 * 4 + ySwitchNum;
//             return switchNum;
//         }
//         x4 = 1;
//         return switchNum;
//     }
// }

u8 witchSwitchPressed(){
    /*
        1、i为行的标识，j为列的标志，switchNum为按键的编号
        2、P20到P23为行的检测，x数组保存检测行对应的数字，比如第一行需要将P20设为0，其余为1，
        对应的二进制数为11111110，十六进制为0xFE,
        3、P24到P27为列的检测如果没有按键被按下，P2的高四位就都为1，如果按下了，高四位的其中
        一位会变为0，比如按下5号按键会变为11101110，通过和00010000按位与就能得知对应位置是否
        为0，如果结果为0，说明对应按键被按下，结果不为零说明没被按下，数组y保存的是需要按位与的数字
    */
    u8 i, j, switchNum;
    u8 x[4] = {0xFE,0xFD,0xFB,0xF7};
    u8 y[4] = {0x10,0x20,0x40,0x80};
    for (i = 0;i < 4;i++){// 扫描行
        P2 = x[i];// 设置检测的行为0
        for (j = 0; j < 4; j++)// 扫描列
        {
            if ((P2 & y[j]) == 0){// 发现按键被按下
                Com_Util_Delay1ms(15);// 跳过按下抖动
                if ((P2 & y[j]) == 0){// 跳过按下抖动后，检测按键是否仍被按下
                    while ((P2 & y[j]) == 0);// 如果仍被按下，等待按键弹起
                    Com_Util_Delay1ms(15);// 按键弹起，跳过弹起抖动
                    switchNum = i * 4 + j + 5;// 返回按下按键的编号，每行按键为4个，行数*4加列数，编号从5开始，最后还要加5
                    return switchNum;
                }
            }
        }
    }
    return 0;// 如果没有按键被按下，返回编号0
}
