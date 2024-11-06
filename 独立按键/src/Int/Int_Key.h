#ifndef __INT_KEY_H__
#define __INT_KEY_H__

#include <STC89C5xRC.H>

#define SW1 P42
#define SW2 P43
#define SW3 P32
#define SW4 P33

/*
    ��ⰴ��1�Ƿ񱻰���
    ����ֵ1��ʾ�����£�0��ʾû������
*/
bit Int_Key_IsSW1Pressed();

/*
    ��ⰴ��2�Ƿ񱻰���
    ����ֵ1��ʾ�����£�0��ʾû������
*/
bit Int_Key_IsSW2Pressed();

/*
    ��ⰴ��3�Ƿ񱻰���
    ����ֵ1��ʾ�����£�0��ʾû������
*/
bit Int_Key_IsSW3Pressed();

/*
    ��ⰴ��4�Ƿ񱻰���
    ����ֵ1��ʾ�����£�0��ʾû������
*/
bit Int_Key_IsSW4Pressed();

#endif /* __INT_KEY_H__ */