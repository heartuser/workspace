#include "stm32f10x.h"                  // Device header
#include "AD.h"

void AD_Init(void)
{
    // 开启时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    // ADC时钟分频
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);
    
    // 配置GPIO
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    // 初始化ADC
    ADC_InitTypeDef ADC_InitStruct;
    ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStruct.ADC_NbrOfChannel = 1;
    ADC_InitStruct.ADC_ScanConvMode = DISABLE;
    ADC_Init(ADC1,&ADC_InitStruct);
    
    // 开启ADC
    ADC_Cmd(ADC1,ENABLE);
    
    // 开启ADC后校准
    ADC_ResetCalibration(ADC1);
    while (ADC_GetResetCalibrationStatus(ADC1) == SET);
    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1) == SET);
    
}

uint16_t AD_GetValue(uint8_t ADC_Channel)
{
    // 选择规则组的输入通道
    ADC_RegularChannelConfig(ADC1,ADC_Channel,1,ADC_SampleTime_239Cycles5);
    // 软件触发转换
    ADC_SoftwareStartConvCmd(ADC1,ENABLE);
    // 等待转换完成
    while (ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);
    
    return ADC_GetConversionValue(ADC1);
}
