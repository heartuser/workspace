#ifndef __DRI_TIMER0_H__
#define __DRI_TIMER0_H__

typedef void (*Timer0_Callback)(void);

void Dri_Timer0_Init();

/**
 * @brief ע��ص�����
 *
 * @param callBack ����ָ��
 * @return bit 0��ע��ʧ��  1��ע��ɹ�
 */
bit Dri_Timer0_RegisterCallBack(Timer0_Callback callBack);

/**
 * @brief ȡ��ע��ص�����
 *
 * @param callBack ����ָ��
 * @return bit 0��ע��ʧ��  1��ע��ɹ�
 */
bit Dri_Timer0_DeregisterCallBack(Timer0_Callback callBack);

#endif /* __DRI_TIMER0_H__ */