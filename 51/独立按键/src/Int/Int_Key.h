#ifndef __INT_KEY_H__
#define __INT_KEY_H__

#include <STC89C5xRC.H>

#define SW1 P42
#define SW2 P43
#define SW3 P32
#define SW4 P33

/*
    检测按键1是否被按下
    返回值1表示被按下，0表示没被按下
*/
bit Int_Key_IsSW1Pressed();

/*
    检测按键2是否被按下
    返回值1表示被按下，0表示没被按下
*/
bit Int_Key_IsSW2Pressed();

/*
    检测按键3是否被按下
    返回值1表示被按下，0表示没被按下
*/
bit Int_Key_IsSW3Pressed();

/*
    检测按键4是否被按下
    返回值1表示被按下，0表示没被按下
*/
bit Int_Key_IsSW4Pressed();

#endif /* __INT_KEY_H__ */