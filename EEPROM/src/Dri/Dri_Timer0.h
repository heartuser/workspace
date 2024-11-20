#ifndef __DRI_TIMER0_H__
#define __DRI_TIMER0_H__

typedef void (*Timer0_Callback)(void);

void Dri_Timer0_Init();

/**
 * @brief 注册回调函数
 *
 * @param callBack 函数指针
 * @return bit 0：注册失败  1：注册成功
 */
bit Dri_Timer0_RegisterCallBack(Timer0_Callback callBack);

/**
 * @brief 取消注册回调函数
 *
 * @param callBack 函数指针
 * @return bit 0：注册失败  1：注册成功
 */
bit Dri_Timer0_DeregisterCallBack(Timer0_Callback callBack);

#endif /* __DRI_TIMER0_H__ */