#include "fan.h"
/*排风扇继电器 PA7*/
#define FanGPIORcc RCC_APB2Periph_GPIOA
#define FanGPIO GPIOA
#define FanGPIOPin GPIO_Pin_7
bool fan_state=1;
/*初始化排风扇继电器 GPIO*/
void init_fan(void)
{
	RCC_APB2PeriphClockCmd(FanGPIORcc,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin=FanGPIOPin;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;//推挽输出
	GPIO_Init(FanGPIO,&GPIO_InitStruct);
	SetFanState(fan_state);
}

/*设置排风扇继电器状态*/
void SetFanState(bool state)
{
	if(state)
	{
		GPIO_SetBits(FanGPIO,FanGPIOPin);
	}else
	{
		GPIO_ResetBits(FanGPIO,FanGPIOPin);
	}
	fan_state=state;
}
/*获取排风扇状态*/
bool GetFanState(void)
{
	return fan_state;
}
