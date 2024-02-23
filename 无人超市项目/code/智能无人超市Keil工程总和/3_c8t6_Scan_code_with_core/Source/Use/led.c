#include "led.h"

/*宏定义 可改LED对应IO口*/
#define RCC_APB_LED_1 RCC_APB2Periph_GPIOG	//LED1的RCC时钟
#define GPIO_LED_1 GPIOG									//LED1的GPIO
#define GPIO_Pin_LED_1 GPIO_Pin_6					//LED1的PIN

#define RCC_APB_LED_2 RCC_APB2Periph_GPIOC	//LED2的RCC时钟
#define GPIO_LED_2 GPIOC										//LED2的GPIO
#define GPIO_Pin_LED_2 GPIO_Pin_13					//LED2的PIN

#define RCC_APB_LED_3 RCC_APB2Periph_GPIOC	//LED3的RCC时钟
#define GPIO_LED_3 GPIOC										//LED3的GPIO
#define GPIO_Pin_LED_3 GPIO_Pin_13					//LED3的PIN

#define RCC_APB_LED_4 RCC_APB2Periph_GPIOC	//LED4的RCC时钟
#define GPIO_LED_4 GPIOC										//LED4的GPIO
#define GPIO_Pin_LED_4 GPIO_Pin_13					//LED4的PIN

/*初始化LED灯的IO口*/
void InitLed(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB_LED_1,ENABLE);//使能LED1的GPIO
	RCC_APB2PeriphClockCmd(RCC_APB_LED_2,ENABLE);//使能LED2的GPIO
	RCC_APB2PeriphClockCmd(RCC_APB_LED_3,ENABLE);//使能LED3的GPIO
	RCC_APB2PeriphClockCmd(RCC_APB_LED_4,ENABLE);//使能LED4的GPIO
	
	{	/*初始化运行 LED GPIO*/
		GPIO_InitTypeDef gpio_init_type;
		gpio_init_type.GPIO_Mode = GPIO_Mode_Out_PP;
		gpio_init_type.GPIO_Speed = GPIO_Speed_50MHz;
		
		gpio_init_type.GPIO_Pin=GPIO_Pin_LED_1;
		GPIO_Init(GPIO_LED_1,&gpio_init_type);
		
		gpio_init_type.GPIO_Pin=GPIO_Pin_LED_2;
		GPIO_Init(GPIO_LED_2,&gpio_init_type);
		
		gpio_init_type.GPIO_Pin=GPIO_Pin_LED_3;
		GPIO_Init(GPIO_LED_3,&gpio_init_type);
		
		gpio_init_type.GPIO_Pin=GPIO_Pin_LED_4;
		GPIO_Init(GPIO_LED_4,&gpio_init_type);
	}
}

/*设置板子上的LED灯的状态(LED，状态)*/
void SetLedState(u8 LED_n,bool state)
{
	if(LED_n==1)
	{
		GPIO_Set_Bit(GPIO_LED_1,GPIO_Pin_LED_1,!state);
	}else
	if(LED_n==2)
	{
		GPIO_Set_Bit(GPIO_LED_2,GPIO_Pin_LED_2,!state);
	}else
	if(LED_n==3)
	{
		GPIO_Set_Bit(GPIO_LED_3,GPIO_Pin_LED_3,!state);
	}else
	if(LED_n==4)
	{
		GPIO_Set_Bit(GPIO_LED_4,GPIO_Pin_LED_4,state);
	}
}
