#include "system.h"

void Init_all(void)//初始化全部
{
	__set_PRIMASK(0);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	SystickInit();
	init_usart1(115200);
	init_usart2(115200);
	init_usart3(115200);
	init_uart4(115200);
	init_uart5(115200);//蓝牙串口初始化(UART5)
	Init_TB6612();//电机驱动初始化(TIM1 ch1 ch2 ch3 ch4 8PIN_GPIO)
	Init_Encoder();//编码器测速初始化(TIM2 TIM3 TIM4 TIM5)
	Init_Graycale();//灰度传感器初始化(I2C)
	Init_Track();//循迹初始化(PID控制)
}
