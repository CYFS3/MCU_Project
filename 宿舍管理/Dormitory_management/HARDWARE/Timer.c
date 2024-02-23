#include "timer.h"

void Door_open(void)
{
    TIM_SetCompare1(TIM3,10);
}
void Door_close(void)
{
    TIM_SetCompare1(TIM3,22);
}


//通用定时器3中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
void TIME3Init(u16 PSC,u16 ARR)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;

    GPIO_Init(GPIOA,&GPIO_InitStructure);

    TIM_DeInit(TIM3);

    TIM_TimeBaseInitStructure.TIM_Prescaler=PSC;
    TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period=ARR;
    TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);


    TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;


    TIM_OC1Init(TIM3,&TIM_OCInitStructure);
    

    TIM_ARRPreloadConfig(TIM3,ENABLE);

    TIM_Cmd(TIM3,ENABLE);
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

}
