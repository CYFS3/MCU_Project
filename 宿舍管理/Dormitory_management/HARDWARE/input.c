#include "config.h"
#include "input.h"


bool LED_Flag = false;
bool WaterFlag = false;

void KEY_EXTI_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    GPIO_InitTypeDef GPIOInitStruct;
    GPIOInitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIOInitStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_4 | GPIO_Pin_3;
    GPIOInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIOInitStruct);
    
    //EXTI中断线对应的GPIO引脚配置，这个函数在stm32f10x_gpio.c里找(易忘，考点)
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource3);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource4);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource5);
    
    EXTI_InitTypeDef EXTI_InitStruct;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStruct.EXTI_Line = EXTI_Line3;
    EXTI_Init(&EXTI_InitStruct);
    EXTI_InitStruct.EXTI_Line = EXTI_Line4;
    EXTI_Init(&EXTI_InitStruct);
    EXTI_InitStruct.EXTI_Line = EXTI_Line5;
    EXTI_Init(&EXTI_InitStruct);
    
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStruct.NVIC_IRQChannel = EXTI3_IRQn;
    NVIC_Init(&NVIC_InitStruct);
    NVIC_InitStruct.NVIC_IRQChannel = EXTI4_IRQn;
    NVIC_Init(&NVIC_InitStruct);
    NVIC_InitStruct.NVIC_IRQChannel = EXTI9_5_IRQn;
    NVIC_Init(&NVIC_InitStruct);
   
}


void EXTI3_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line3) == SET)
    {
        rc_state.RC_OK = 1;
        EXTI_ClearITPendingBit(EXTI_Line3);
    }
}
    


void EXTI4_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line4) == SET)
    {
        switch_state = !switch_state;
        MQTT_Send_LED(switch_state);
        EXTI_ClearITPendingBit(EXTI_Line4);
    }
}
void EXTI9_5_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line5) == SET)
    {
        sluice_state = !sluice_state;
        MQTT_Send_Water(sluice_state);
        EXTI_ClearITPendingBit(EXTI_Line5);
    }
}




