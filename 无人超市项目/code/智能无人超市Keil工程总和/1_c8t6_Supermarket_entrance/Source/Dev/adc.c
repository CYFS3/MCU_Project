#include "adc.h"

/*初始化ADC1*/
void adc1_init(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1,ENABLE);//使能GPIO和ADC1的外设
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);  //分频6(72/6)
	/*载入GPIOA*/
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AIN;//模拟输入
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	ADC_DeInit(ADC1);  //复位ADC1
	/*初始化ADC配置*/
	ADC_InitTypeDef ADC_InitStruct;
	ADC_InitStruct.ADC_Mode=ADC_Mode_Independent;  //独立模式。因为只用一个adc。
	ADC_InitStruct.ADC_ScanConvMode=DISABLE;     //扫描转换使能
	ADC_InitStruct.ADC_ContinuousConvMode=DISABLE;  //连续转换使能
	ADC_InitStruct.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;//外部触发
	ADC_InitStruct.ADC_DataAlign=ADC_DataAlign_Right;   //数据对齐，右对齐，左对齐要除16
	ADC_InitStruct.ADC_NbrOfChannel=1;   //通道数目
	ADC_Init(ADC1,&ADC_InitStruct);//加载ADC配置进ADC1
  ADC_Cmd(ADC1,ENABLE);//使能启用ADC1
	ADC_ResetCalibration(ADC1);//使能后校准
	while(ADC_GetResetCalibrationStatus(ADC1)==SET);
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1)==SET);
}

/*获取ADC1的转换值*/
u16 Get_adc1(u8 channel)
{
	ADC_RegularChannelConfig(ADC1,channel,1,ADC_SampleTime_55Cycles5);
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);  //软件启动转换
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET); //获取转换完成的标志位
	return ADC_GetConversionValue(ADC1);
}

/*获取ADC1转化后的平均值*/
u16 Get_Adc1_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_adc1(ch);
		DelayMs(5);
	}
	return temp_val/times;
}
