#include "beep.h"
/*蜂鸣器 PA6*/
#define BeepGPIORcc RCC_APB2Periph_GPIOA
#define BeepGPIO GPIOA
#define BeepGPIOPin GPIO_Pin_6
bool BeepState=0;
/*初始化蜂鸣器GPIO*/
void init_beep(void)
{
	RCC_APB2PeriphClockCmd(BeepGPIORcc,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin=BeepGPIOPin;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;//推挽输出
	GPIO_Init(BeepGPIO,&GPIO_InitStruct);
	SetBeepState(BeepState);
}

/*设置蜂鸣器状态*/
void SetBeepState(bool state)
{
	if(state)
	{
		GPIO_SetBits(BeepGPIO,BeepGPIOPin);
	}else
	{
		GPIO_ResetBits(BeepGPIO,BeepGPIOPin);
	}
	BeepState=state;
}
/*获取蜂鸣器状态*/
bool GetBeepState(void)
{
	return BeepState;
}
