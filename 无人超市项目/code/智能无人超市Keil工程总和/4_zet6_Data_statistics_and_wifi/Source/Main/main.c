#include "config.h"
void init_all(void);
void RunAllTask(void);
/*----------Main主函数-----------*/
int main()
{
	init_all();//初始化所有
	while(1)
	{
		RunAllTask();
	}
}
/*-----------Main结束------------*/

void init_all(void)
{/*初始化所有*/
	SysInit();//初始化系统时钟与中断
	InitLed();//led初始化
	init_all_data();//初始化所有数据结构
	init_usart1(115200);//初始化串口1(PC调试) PA9 PA10
	init_usart2(115200);//初始化串口2(连接到超市入口c8t6单片机)PA2 PA3
	init_usart3(115200);//初始化串口3(连接到传感器c8t6单片机)PB10 PB11
	init_uart4(115200);//初始化串口4(连接到扫码处c8t6单片机)PC10 PC11
	init_uart5(115200);//初始化串口5(连接到ESP8266 WIFI模块)PC12 PD2
	init_wifi();//初始化wifi
}

void RunAllTask(void)
{/*执行任务*/
	Task1();
	Task2();
	Task3();
	Task4();
	USART1_RecProcess();
	USART2_RecProcess();
	USART3_RecProcess();
	UART4_RecProcess();
	UART5_RecProcess();
}
