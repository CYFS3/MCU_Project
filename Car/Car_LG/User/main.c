#include  "config.h"

void SysInit(void);

int main()
{
	SysInit();
	Car_Front();
    //Set_PWM_Legh(1000);
    //Set_PWM_Right(1000);
	while(1)
	{
		task_Run_All();
	}
}


void SysInit(void)
{
	CPU_INT_ENABLE();//开总中断
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级
	SystickInit();//滴答时钟初始化
	TaskInit();
	Init_TB6612();
	USARTInit();
   // init_usart2(115200);
    Init_Encoder();
    PID_Init();
    Car_Front();
    QueueInit();
}
