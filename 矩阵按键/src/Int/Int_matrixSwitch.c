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
    u8 i, j, switchNum;
    u8 x[4] = {0xFE,0xFD,0xFB,0xF7};
    u8 y[4] = {0x10,0x20,0x40,0x80};
    for (i = 0;i < 4;i++){
        P2 = x[i];
        for (j = 0; j < 4; j++)
        {
            if ((P2 & y[j]) == 0){
                Com_Util_Delay1ms(15);
                if ((P2 & y[j]) == 0){
                    while ((P2 & y[j]) == 0);
                    Com_Util_Delay1ms(15);
                    switchNum = i * 4 + j + 1;
                    return switchNum;
                }
            }
        }
    }
    return 0;
}
