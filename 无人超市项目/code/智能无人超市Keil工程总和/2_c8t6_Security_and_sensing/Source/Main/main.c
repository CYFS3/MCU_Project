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
	SysInit();//初始化系统时钟与中断
	InitLed();//led初始化
	init_usart1(115200);//初始化串口1(电脑调试)
	init_usart2(115200);//初始化串口2(连接到总控制stm32f103zet6)
	LCD_Init();//LCD初始化
	init_data();//初始化数据
	init_lcd_word();//LCD屏幕文字初始化

	DHT11_Init();//dht11温湿度初始化
	adc1_init();//初始化(ADC1)光强与烟雾传感器
	init_fire_sensor();//初始化火焰传感器
	init_big_led();//初始化大灯
	init_fan();//初始化排风扇
	init_beep();//初始化蜂鸣器
	
}

void RunAllTask(void)
{/*执行任务*/
	Task1();
	Task2();
	Task3();
	Task4();
	Task5();
	USART2_RecProcess();//串口2接收任务
}
