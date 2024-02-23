#include "big_led.h"
/*BIG LED PA4*/
#define LedGPIORcc RCC_APB2Periph_GPIOA
#define LedGPIO GPIOA
#define LedGPIOPin GPIO_Pin_4
bool BigLedState=1;
/*初始化BIG LED GPIO*/
void init_big_led(void)
{
	RCC_APB2PeriphClockCmd(LedGPIORcc,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin=LedGPIOPin;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;//推挽输出
	GPIO_Init(LedGPIO,&GPIO_InitStruct);
	SetBigLedState(BigLedState);
}

/*设置BIG LED状态*/
void SetBigLedState(bool state)
{
	if(state)
	{
		GPIO_SetBits(LedGPIO,LedGPIOPin);
	}else
	{
		GPIO_ResetBits(LedGPIO,LedGPIOPin);
	}
	BigLedState=state;
}
/*获取大灯的状态*/
bool GetBigLedState(void)
{
	return BigLedState;
}

