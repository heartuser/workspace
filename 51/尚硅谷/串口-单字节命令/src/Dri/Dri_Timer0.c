#include <STC89C5xRC.H>
#include <STDIO.H>
#include "Dri_Timer0.h"
#include "Com_Util.h"

#define MAX_CALLBACK_COUNT 4

static Timer0_Callback s_callbacks[MAX_CALLBACK_COUNT];

void Dri_Timer0_Init()
{
    u8 i;
    // ���ж��ܿ���
    EA = 1;
    // �򿪶�ʱ��0�жϿ���
    ET0 = 1;
    // ��ʱ��0������ʽ(GATE=0��C/T=0��M1=0��M0=1)
    TMOD &= 0xF0;
    TMOD |= 0x01;
    // ���������������ʼֵ������Ƶ��11.0592MHz,16λ���Զ�����ģʽ��1ms��
    TL0 = 0x66;
    TH0 = 0xFC;
    // ������ʱ��
    TR0 = 1;

    // ��ʼ������ָ�������ֵ
    for (i = 0; i < MAX_CALLBACK_COUNT; i++) {
        s_callbacks[i] = NULL;
    }
    
}

bit Dri_Timer0_RegisterCallBack(Timer0_Callback callBack)
{
    u8 i;
    for (i = 0; i < MAX_CALLBACK_COUNT; i++) { // ��ֹ�ظ�ע��
        if (s_callbacks[i] == callBack) {
            return 1;
        }
    }

    for (i = 0; i < MAX_CALLBACK_COUNT; i++) { // Ѱ�ҿ�λ����ע��
        if (s_callbacks[i] == NULL) {
            s_callbacks[i] = callBack;
            return 1;
        }
    }

    return 0; // �Ȳ�����ָ������ָ�룬Ҳû�п�λ��ע��ʧ��
}

bit Dri_Timer0_DeregisterCallBack(Timer0_Callback callBack)
{
    u8 i;
    for (i = 0; i < MAX_CALLBACK_COUNT; i++) {
        if (s_callbacks[i] == callBack) {
            s_callbacks[i] = NULL;
            return 1;
        }
    }
    return 0;
}

// ��ʱ��0���жϷ������
void timer0Handler() interrupt 1
{
    u8 i;
    // ��ʼ����ʱ����ֵ
    TL0 = 0x66;
    TH0 = 0xFC;

    for (i = 0; i < MAX_CALLBACK_COUNT; i++) {
        if (s_callbacks[i] != NULL) {
            s_callbacks[i]();
        }
    }
}