#include "fire.h"
/*火焰传感器 PA5*/
#define FireGPIORcc RCC_APB2Periph_GPIOA
#define FireGPIO GPIOA
#define FireGPIOPin GPIO_Pin_5
/*初始化火焰传感器*/
void init_fire_sensor(void)
{
	RCC_APB2PeriphClockCmd(FireGPIORcc,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin=FireGPIOPin;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(FireGPIO,&GPIO_InitStruct);
}

/*获取火焰状态*/
bool GetFireState(void)
{
	return !GPIO_ReadInputDataBit(FireGPIO,FireGPIOPin);
}
