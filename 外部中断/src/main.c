#include <STC89C5xRC.H>
#include "Com_Util.h"

void INT0_Init()
{
    // �����ж��ܿ���
    EA = 1;
    // ����0��1���ⲿ�ж�
    EX0 = 1;
    EX1 = 1;
    // ����0�š����ⲿ�ж�Ϊ�½��ش���
    IT0 = 1;
    IT1 = 1;
    // ����1���ⲿ�ж����ȼ�Ϊ1.1����߼�����0���ⲿ�ж�û�������ȼ�Ĭ��Ϊ��ͼ���0.0��
    IPH = 0X02;
    PX1 = 1;
}

// �ⲿ�ж�0���ȼ����ⲿ�ж�1�ͣ�����sw3��LED1��˸����˸��ͬʱ��sw4�Կ��л�LED2������
void main()
{   
    INT0_Init();
    while (1) {
    }
}

// 0���ⲿ�жϵķ������
void INT0_Handler() interrupt 0
{
    Com_Util_Delay1ms(15);
    while (1)
    {
        P20 = ~P20;
        Com_Util_Delay1ms(500);
    }
    
}

// 1���ⲿ�жϵķ������
void INT1_Handler() interrupt 2
{
    Com_Util_Delay1ms(15);
    if (P33 == 0){
        P21 = ~P21;
    }
}