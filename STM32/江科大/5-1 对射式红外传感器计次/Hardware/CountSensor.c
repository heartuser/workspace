#include "stm32f10x.h"                  // Device header
#include "CountSensor.h"
#include "Delay.h"

uint16_t CountSensor_count;

void CountSensor_Init(void)
{
    /*开启GPIO和中断时钟（EXTI和NVIC不需要开启时钟，默认开启）
      NVIC是内核外设，内核外设都是默认开启
    */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    // 配置GPIO
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // AFIO外部中断引脚选择配置
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);

    // EXTI配置
    EXTI_InitTypeDef EXTI_InitStruct;
    EXTI_InitStruct.EXTI_Line = EXTI_Line14;// 中断线选择
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;// 开启中断线
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;// 选择中断模式还是事件模式，这里是中断模式
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;// 上升沿触发

    EXTI_Init(&EXTI_InitStruct);

    // 配置NVIC
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 2位抢占优先级，2位响应优先级（数字代表抢占优先级的位数）

    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;

    NVIC_Init(&NVIC_InitStructure);
}

// 中断函数（不同中断的函数名是固定的，到启动文件中查找）
void EXTI15_10_IRQHandler(void)
{
    // 判断是不是14号中断线触发
    if (EXTI_GetITStatus(EXTI_Line14) == SET)
    {
        // 延时和判断都是为了消抖（下降沿触发判断是否等于0，上升和下降都触发不加判断）
        Delay_ms(5);
        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 1)
        {
            // 计数加一
            CountSensor_count++;
        }
        
        // 清除中断标志位(否则会一直执行中断函数)
        EXTI_ClearITPendingBit(EXTI_Line14);
        
    }
}

uint16_t CountSensor_GET(void)
{
    return CountSensor_count;
}
