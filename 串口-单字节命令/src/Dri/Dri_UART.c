#include "Dri_UART.h"
#include <STC89C5xRC.H>
#include "Com_Util.h"
#include "Dri_Timer0.h"

static bit s_is_sending  = 0; // 0��ʾδ�ڷ��ͣ�1��ʾ���ڷ���
static char s_buffer[16] = 0;
static u8 s_index        = 0;
static u8 s_idle_count   = 0; // 1ms��1
static bit s_is_complete = 0; // �Ƿ������ɱ�־ 0��û�����꣬1���������

void Dri_UART_Timer0CallBack()
{
    s_idle_count++;
    if (s_index > 0 && s_idle_count > 10) { // ˵���������
        s_is_complete = 1;
    }
}

void Dri_UART_Init()
{
    // 1.���ڵĹ���ģʽ
    SM0 = 0;
    SM1 = 1;

    // 2.������(9600)
    // 2.1 SMOD
    PCON &= 0X7F; // SMOD = 0
    // 2.2 ��ʱ��1������
    // 2.2.1 ��ʱ��1�Ĺ���ģʽ
    TMOD &= 0x0F;
    TMOD |= 0X2F;
    // 2.2.2 ���ö�ʱ��1�ĳ�ʼֵ
    TH1 = 253;
    TH1 = 253;
    // 2.2.3 ������ʱ��
    TR1 = 1;

    // 3.���ڽ�������
    REN = 1; // ����ʹ��
    SM2 = 0; // �Ƿ������λ��0Ϊ�����

    // 4.�����ж�����
    EA = 1; // �ж��ܿ���
    ES = 1; // �����жϿ���
    RI = 0; // �����жϱ�־λ
    TI = 0; // �����жϱ�־λ

    // 5.��Timer0ע��������ݼ����ص�����
    Dri_Timer0_RegisterCallBack(Dri_UART_Timer0CallBack);
}

// ���͵����ַ�
void Dri_UART_SendChar(char c)
{
    while (s_is_sending == 1);
    s_is_sending = 1;
    SBUF         = c;
}

// �����ַ���
void Dri_UART_SendStr(char *str)
{
    while (*str != 0) {
        Dri_UART_SendChar(*str);
        str++;
    }
}

// �����ַ���
bit Dri_UART_RecevieStr(char *str)
{
    if (s_is_complete == 1) {
        u8 i;
        for (i = 0; i < s_index; i++) {
            str[i] = s_buffer[i];
        }
        str[i]        = '\0';
        s_is_complete = 0;
        s_index       = 0;
        return 1;
    }
    return 0;
}

void Dri_UART_Handler() interrupt 4
{
    // �����������
    if (RI == 1) {
        s_buffer[s_index++] = SBUF;
        s_idle_count        = 0;
        RI                  = 0;
    }

    // ����������
    if (TI == 1) {
        s_is_sending = 0;
        TI           = 0;
    }
}