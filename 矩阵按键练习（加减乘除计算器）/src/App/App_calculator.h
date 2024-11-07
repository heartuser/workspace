#ifndef __APP_CALCULATOR_H__
#define __APP_CALCULATOR_H__

#include "Com_Util.h"

u8 isNum(u8 switchNum);
u8 pressedOperator(u8 switchNum);
void inputPoint();
double getResult(double num1, double num2);
double buildNumber(double num, u8 sigleNum);

#endif /* __APP_CALCULATOR_H__ */