#include "Car_TB6612.h"


/************************宏定义区*******************************/
#define RCC_CAR_GPIO RCC_APB2Periph_GPIOC
#define CAR_GPIO GPIOC
#define CAR_LEFT_FRONT_GPIOPIN1 GPIO_Pin_0
#define CAR_LEFT_FRONT_GPIOPIN2 GPIO_Pin_1
#define	CAR_LEFT_BACK_GPIOPIN1 GPIO_Pin_2
#define	CAR_LEFT_BACK_GPIOPIN2 GPIO_Pin_3
#define CAR_RIGHT_FRONT_GPIOPIN1 GPIO_Pin_4
#define CAR_RIGHT_FRONT_GPIOPIN2 GPIO_Pin_5
#define CAR_RIGHT_BACK_GPIOPIN1 GPIO_Pin_6
#define CAR_RIGHT_BACK_GPIOPIN2 GPIO_Pin_7
/*************************************************************/




/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    Car_Control_Init
  * @brief  
  * @param   None
  * @retval
  * @author  CYFS
  * @Data    2023-07-24
	* TB6612逻辑引脚初始化
	* 左前轮 PIN1->PC0
	*	 	     PIN2->PC1
	* 左后轮 PIN1->PC2
	* 			 PIN2->PC3
	* 右前轮 PIN1->PC4
	* 			 PIN2->PC5
	* 右后轮 PIN1->PC6
  *		     PIN2->PC7
 **/
/* -------------------------------- end -------------------------------- */
void Car_Control_Init(void)
{
	GPIO_InitTypeDef GPIOInitStruct;
	RCC_APB2PeriphClockCmd(RCC_CAR_GPIO, ENABLE);//开启CARGPIO时钟
	GPIOInitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIOInitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	//左前轮
	GPIOInitStruct.GPIO_Pin=CAR_LEFT_FRONT_GPIOPIN1|CAR_LEFT_FRONT_GPIOPIN2;
	GPIO_Init(CAR_GPIO, &GPIOInitStruct);
	//左后轮
	GPIOInitStruct.GPIO_Pin=CAR_LEFT_BACK_GPIOPIN1|CAR_LEFT_BACK_GPIOPIN2;
	GPIO_Init(CAR_GPIO, &GPIOInitStruct);
	//右前轮
	GPIOInitStruct.GPIO_Pin=CAR_RIGHT_FRONT_GPIOPIN1|CAR_RIGHT_FRONT_GPIOPIN1;
	GPIO_Init(CAR_GPIO, &GPIOInitStruct);
	//右后轮
	GPIOInitStruct.GPIO_Pin=CAR_RIGHT_BACK_GPIOPIN1|CAR_RIGHT_BACK_GPIOPIN2;
	GPIO_Init(CAR_GPIO, &GPIOInitStruct);
	
	//初始化完成，车处于停止状态
	//左前轮
	GPIO_ResetBits(CAR_GPIO,CAR_LEFT_FRONT_GPIOPIN1);
	GPIO_ResetBits(CAR_GPIO,CAR_LEFT_FRONT_GPIOPIN2);
	//左后轮
	GPIO_ResetBits(CAR_GPIO,CAR_LEFT_BACK_GPIOPIN1);
	GPIO_ResetBits(CAR_GPIO,CAR_LEFT_BACK_GPIOPIN2);
	//右前轮
	GPIO_ResetBits(CAR_GPIO,CAR_RIGHT_FRONT_GPIOPIN1);
	GPIO_ResetBits(CAR_GPIO,CAR_RIGHT_FRONT_GPIOPIN2);
	//右后轮
	GPIO_ResetBits(CAR_GPIO,CAR_RIGHT_BACK_GPIOPIN1);
	GPIO_ResetBits(CAR_GPIO,CAR_RIGHT_BACK_GPIOPIN2);
	
}

/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    Car_Front
  * @brief  
  * @param   None
  * @retval
  * @author  CYFS
  * @Data    2023-07-24
  * 控制小车往前，四路电机正转。
 **/
/* -------------------------------- end -------------------------------- */
void Car_Front(void)
{
	//小车状态往前
	//左前轮
	GPIO_ResetBits(CAR_GPIO,CAR_LEFT_FRONT_GPIOPIN1);
	GPIO_SetBits(CAR_GPIO,CAR_LEFT_FRONT_GPIOPIN2);
	//左后轮
	GPIO_ResetBits(CAR_GPIO,CAR_LEFT_BACK_GPIOPIN1);
	GPIO_SetBits(CAR_GPIO,CAR_LEFT_BACK_GPIOPIN2);
	//右前轮
	GPIO_ResetBits(CAR_GPIO,CAR_RIGHT_FRONT_GPIOPIN1);
	GPIO_SetBits(CAR_GPIO,CAR_RIGHT_FRONT_GPIOPIN2);
	//右后轮
	GPIO_ResetBits(CAR_GPIO,CAR_RIGHT_BACK_GPIOPIN1);
	GPIO_SetBits(CAR_GPIO,CAR_RIGHT_BACK_GPIOPIN2);
	
}


/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    TB6612_Init_All
  * @brief  
  * @param   None
  * @retval
  * @author  CYFS
  * @Data    2023-07-24
	* 初始化TB6612：1.逻辑控制引脚 2.PWM输出控制
 **/
/* -------------------------------- end -------------------------------- */
void Init_TB6612(void)
{
	Car_Control_Init();//逻辑引脚初始化
	Car_PWM_Init();//PWM输出初始化
}
/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    Car_Back
  * @brief  
  * @param   None
  * @retval
  * @author  CYFS
  * @Data    2023-07-24
  * 控制小车往后，四路电机反转
 **/
/* -------------------------------- end -------------------------------- */
void Car_Back(void)
{
	//小车状态往后
	//左前轮
	GPIO_SetBits(CAR_GPIO,CAR_LEFT_FRONT_GPIOPIN1);
	GPIO_ResetBits(CAR_GPIO,CAR_LEFT_FRONT_GPIOPIN2);
	//左后轮
	GPIO_SetBits(CAR_GPIO,CAR_LEFT_BACK_GPIOPIN1);
	GPIO_ResetBits(CAR_GPIO,CAR_LEFT_BACK_GPIOPIN2);
	//右前轮
	GPIO_SetBits(CAR_GPIO,CAR_RIGHT_FRONT_GPIOPIN1);
	GPIO_ResetBits(CAR_GPIO,CAR_RIGHT_FRONT_GPIOPIN2);
	//右后轮
	GPIO_SetBits(CAR_GPIO,CAR_RIGHT_BACK_GPIOPIN1);
	GPIO_ResetBits(CAR_GPIO,CAR_RIGHT_BACK_GPIOPIN2);
}

/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    Car_Stop
  * @brief  
  * @param   None
  * @retval
  * @author  CYFS
  * @Data    2023-07-24
	* 控制小车处于禁止状态，四路电机不转。
**/
/* -------------------------------- end -------------------------------- */
void Car_Stop(void)
{
	//小车处于停止状态
	//左前轮
	GPIO_ResetBits(CAR_GPIO,CAR_LEFT_FRONT_GPIOPIN1);
	GPIO_ResetBits(CAR_GPIO,CAR_LEFT_FRONT_GPIOPIN2);
	//左后轮
	GPIO_ResetBits(CAR_GPIO,CAR_LEFT_BACK_GPIOPIN1);
	GPIO_ResetBits(CAR_GPIO,CAR_LEFT_BACK_GPIOPIN2);
	//右前轮
	GPIO_ResetBits(CAR_GPIO,CAR_RIGHT_FRONT_GPIOPIN1);
	GPIO_ResetBits(CAR_GPIO,CAR_RIGHT_FRONT_GPIOPIN2);
	//右后轮
	GPIO_ResetBits(CAR_GPIO,CAR_RIGHT_BACK_GPIOPIN1);
	GPIO_ResetBits(CAR_GPIO,CAR_RIGHT_BACK_GPIOPIN2);
	
}

/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    Car_PWM_Init
  * @brief  
  * @param   None
  * @retval
  * @author  CYFS
  * @Data    2023-07-24
	* TB6612 TIM1初始化输出四路PWM波 
	* CH1->PE9 CH2->PE11 CH3->PE13 CH4->PE15 (完全重映射)
 **/
/* -------------------------------- PWM初始化 -------------------------------- */
void Car_PWM_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	// 打开GPIOE和TIM1的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE | RCC_APB2Periph_TIM1 | RCC_APB2Periph_AFIO , ENABLE); 
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM1,ENABLE);//完全重映射TIM1
	// 配置GPIOE：TIM1 Channel1~4作为推挽复用输出
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9 | GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	// 时基配置
	TIM_TimeBaseStructure.TIM_Period = 999; // PWM周期设置为1000，即1ms
	TIM_TimeBaseStructure.TIM_Prescaler = 71; // 预分频系数为72，即1MHz
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

	// PWM1模式配置：Channel1~4
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0; // PWM占空比为1/1000=0.1%
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);

	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM1, ENABLE);

	// 启动TIM1计数器
	TIM_Cmd(TIM1, ENABLE);
	TIM_CtrlPWMOutputs(TIM1,ENABLE);// MOE 主输出使能
}

//设置PWM占空比的函数(传入compare)
void Set_PWM_Compare1(uint16_t pulse)
{
    TIM_SetCompare1(TIM1, pulse);
}
void Set_PWM_Compare2(uint16_t pulse)
{
    TIM_SetCompare2(TIM1, pulse);
}
void Set_PWM_Compare3(uint16_t pulse)
{
    TIM_SetCompare3(TIM1, pulse);
}
void Set_PWM_Compare4(uint16_t pulse)
{
    TIM_SetCompare4(TIM1, pulse);
}

// 设置PWM占空比的函数(直接传入float%)
void Set_PWM_percent1(float duty_cycle)//0.1
{
    TIM_SetCompare1(TIM1, (uint16_t)(999-(duty_cycle / 100.0f * 999)));
}
void Set_PWM_percent2(float duty_cycle)
{
    TIM_SetCompare2(TIM1, (uint16_t)(999-(duty_cycle / 100.0f * 999)));
}
void Set_PWM_percent3(float duty_cycle)
{
    TIM_SetCompare3(TIM1, (uint16_t)(999-(duty_cycle / 100.0f * 999)));
}
void Set_PWM_percent4(float duty_cycle)
{
    TIM_SetCompare4(TIM1, (uint16_t)(999-(duty_cycle / 100.0f * 999)));
}
// 紧急刹车函数
void BrakeCar(void)
{
    // 关闭PWM输出
    TIM_CtrlPWMOutputs(TIM1, DISABLE);
}

// 重启函数
void RestartCar(void)
{
    // 重新启动PWM输出
    TIM_CtrlPWMOutputs(TIM1, ENABLE);
}
