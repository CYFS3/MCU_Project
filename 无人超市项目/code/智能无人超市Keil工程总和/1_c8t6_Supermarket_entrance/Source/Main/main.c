#include "config.h"
void init_all(void);
void RunAllTask(void);
/*----------Main主函数-----------*/
int main()
{
	init_all();//初始化所有
	while(1)
	{
		RunAllTask();//执行任务
	}
}
/*-----------Main结束------------*/

void init_all(void)
{/*初始化所有*/
	init_usart1(115200);//初始化串口1

	SysInit();//初始化系统时钟与中断

	InitLed();//led初始化

	pir_init();//人体红外初始化
	
  Servo_Init();//舵机初始化
	
	init_lcd_word();//初始化LCD屏幕
	
	close_door();
}

void RunAllTask(void)
{/*执行任务*/
	Task1();
	Task2();
	Task3();
	Task4();
	USART1_RecProcess();
}
