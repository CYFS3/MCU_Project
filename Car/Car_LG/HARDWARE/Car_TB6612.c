#include "Car_TB6612.h"


/************************宏定义区*******************************/
#define RCC_CAR_GPIO RCC_APB2Periph_GPIOF
#define CAR_GPIO GPIOF
#define	CAR_LEFT_BACK_GPIOPIN1 GPIO_Pin_11
#define	CAR_LEFT_BACK_GPIOPIN2 GPIO_Pin_12
#define CAR_RIGHT_BACK_GPIOPIN1 GPIO_Pin_13
#define CAR_RIGHT_BACK_GPIOPIN2 GPIO_Pin_14
/*************************************************************/




void Car_Control_Init(void)
{
	GPIO_InitTypeDef GPIOInitStruct;
	RCC_APB2PeriphClockCmd(RCC_CAR_GPIO, ENABLE);//开启CARGPIO时钟
	GPIOInitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIOInitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	//左后轮
	GPIOInitStruct.GPIO_Pin=CAR_LEFT_BACK_GPIOPIN1|CAR_LEFT_BACK_GPIOPIN2;
	GPIO_Init(CAR_GPIO, &GPIOInitStruct);
	//右后轮
	GPIOInitStruct.GPIO_Pin=CAR_RIGHT_BACK_GPIOPIN1|CAR_RIGHT_BACK_GPIOPIN2;
	GPIO_Init(CAR_GPIO, &GPIOInitStruct);
	
	//初始化完成，车处于停止状态
	//左后轮
	GPIO_ResetBits(CAR_GPIO,CAR_LEFT_BACK_GPIOPIN1);
	GPIO_ResetBits(CAR_GPIO,CAR_LEFT_BACK_GPIOPIN2);
	//右后轮
	GPIO_ResetBits(CAR_GPIO,CAR_RIGHT_BACK_GPIOPIN1);
	GPIO_ResetBits(CAR_GPIO,CAR_RIGHT_BACK_GPIOPIN2);
}

void Car_Front(void)
{
	//小车状态往前
	
	//左后轮
	GPIO_ResetBits(CAR_GPIO,CAR_LEFT_BACK_GPIOPIN1);
	GPIO_SetBits(CAR_GPIO,CAR_LEFT_BACK_GPIOPIN2);
	//右后轮
	GPIO_ResetBits(CAR_GPIO,CAR_RIGHT_BACK_GPIOPIN1);
	GPIO_SetBits(CAR_GPIO,CAR_RIGHT_BACK_GPIOPIN2);
	
	
}



void Car_Right(void)
{
	//小车状态往前
	
	//左后轮
	GPIO_ResetBits(CAR_GPIO,CAR_LEFT_BACK_GPIOPIN1);
	GPIO_SetBits(CAR_GPIO,CAR_LEFT_BACK_GPIOPIN2);
	//右后轮
	GPIO_ResetBits(CAR_GPIO,CAR_RIGHT_BACK_GPIOPIN1);
	GPIO_SetBits(CAR_GPIO,CAR_RIGHT_BACK_GPIOPIN2);
	
}
void Car_Left(void)
{
	//小车状态往前
	
	//左后轮
	GPIO_ResetBits(CAR_GPIO,CAR_LEFT_BACK_GPIOPIN1);
	GPIO_SetBits(CAR_GPIO,CAR_LEFT_BACK_GPIOPIN2);
	//右后轮
	GPIO_ResetBits(CAR_GPIO,CAR_RIGHT_BACK_GPIOPIN1);
	GPIO_SetBits(CAR_GPIO,CAR_RIGHT_BACK_GPIOPIN2);
	

}


void Init_TB6612(void)
{
	Car_Control_Init();//逻辑引脚初始化
	Car_PWM_Init();//PWM输出初始化
}

void Car_Back(void)
{
	//小车状态往后
	//左后轮
	GPIO_SetBits(CAR_GPIO,CAR_LEFT_BACK_GPIOPIN1);
	GPIO_ResetBits(CAR_GPIO,CAR_LEFT_BACK_GPIOPIN2);
	//右后轮
	GPIO_SetBits(CAR_GPIO,CAR_RIGHT_BACK_GPIOPIN1);
	GPIO_ResetBits(CAR_GPIO,CAR_RIGHT_BACK_GPIOPIN2);

	
}


void Car_Stop(void)
{
	//小车处于停止状态
	
	//左后轮
	GPIO_ResetBits(CAR_GPIO,CAR_LEFT_BACK_GPIOPIN1);
	GPIO_ResetBits(CAR_GPIO,CAR_LEFT_BACK_GPIOPIN2);
	//右后轮
	GPIO_ResetBits(CAR_GPIO,CAR_RIGHT_BACK_GPIOPIN1);
	GPIO_ResetBits(CAR_GPIO,CAR_RIGHT_BACK_GPIOPIN2);
	
}

void Car_PWM_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE); 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	// 时基配置
	TIM_TimeBaseStructure.TIM_Period = 999; // PWM周期设置为1000，即1ms
	TIM_TimeBaseStructure.TIM_Prescaler = 71; // 预分频系数为72，即1MHz
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	// PWM1模式配置：Channel1~4
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM4, ENABLE);

	// 启动TIM3计数器
	TIM_Cmd(TIM4, ENABLE);
    
    
}




void Set_PWM_Right(uint16_t duty_cycle)
{
    TIM4->CCR1 = duty_cycle;
}
void Set_PWM_Legh(uint16_t duty_cycle)
{
    TIM4->CCR2 = duty_cycle;
}

