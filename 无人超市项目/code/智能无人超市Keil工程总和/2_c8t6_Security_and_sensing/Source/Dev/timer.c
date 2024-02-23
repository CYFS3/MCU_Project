#include "timer.h"

/*以PWM输出模式初始化定时器3*/
void PWM_TIM3_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure; //GPIO初始化配置结构体
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure; //定时器3初始化配置结构体
	TIM_OCInitTypeDef  TIM_OCInitStructure; //定时器通道配置结构体
	
	/*给定时器外设和GPIO和AFIO复用都使能*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);

	/*PWM输出通道的GPIO初始化*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7; //对应TIM3的通道1与通道2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化GPIO
 
  /*初始化定时器3*/
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	/*初始化通道配置为：PWM1模式输出*/
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //TIM脉冲宽度调制模式1
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //应用通道配置到TIM3的通道1
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //应用通道配置到TIM3的通道2
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR1上的预装载寄存器
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器

	TIM_Cmd(TIM3, ENABLE);  //使能定时器3
}

/*设置定时器3中通道1和通道2的PWM输出的比较值*/
void SetTIM3PWMCompare(uint16_t Compare1,uint16_t Compare2)
{
	TIM_SetCompare1(TIM3, Compare1);
	TIM_SetCompare2(TIM3, Compare2);
}
