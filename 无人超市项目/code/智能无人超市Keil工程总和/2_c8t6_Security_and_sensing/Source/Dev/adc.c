#include "adc.h"

/*初始化ADC1*/
void adc1_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE);
	// 光强传感器
	GPIO_InitStructure.GPIO_Pin = LIGHT_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(LIGHT_PORT, &GPIO_InitStructure);
	// 烟雾传感器
	GPIO_InitStructure.GPIO_Pin = MQ_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(MQ_PORT, &GPIO_InitStructure);
	
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 2;//两个通道
	ADC_Init(ADCx, &ADC_InitStructure);
	// 通道0：光强传感器
	ADC_RegularChannelConfig(ADCx, LIGHT_CHANNEL, 1, ADC_SampleTime_239Cycles5);
	// 通道1：烟雾传感器
	ADC_RegularChannelConfig(ADCx, MQ_CHANNEL, 2, ADC_SampleTime_239Cycles5);
	ADC_Cmd(ADCx, ENABLE);
	ADC_ResetCalibration(ADC1);//使能后校准
	while(ADC_GetResetCalibrationStatus(ADC1)==SET);
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1)==SET);
}

/*获取ADC1的转换值*/
u16 Get_adc1(u8 channel)
{
	ADC_RegularChannelConfig(ADCx, channel, 1, ADC_SampleTime_239Cycles5);
  ADC_SoftwareStartConvCmd(ADCx, ENABLE);
	while (!ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC));
	return ADC_GetConversionValue(ADCx);
}

/*获取ADC1转化后的平均值*/
u16 Get_Adc1_Average(u8 channel,u8 times)
{                                                                                   
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_adc1(channel);
		DelayMs(5);
	}
	return temp_val/times;
}
