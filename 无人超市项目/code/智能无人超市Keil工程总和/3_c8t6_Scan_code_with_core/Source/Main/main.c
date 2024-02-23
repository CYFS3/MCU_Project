#include "config.h"
#include "led.h"
void init_all(void);
void RunAllTask(void);

/*----------Main主函数-----------*/
int main()
{
	init_all();//初始化全部
	Door_ON();
	while(1)
	{
		RunAllTask();//运行任务
	}
}
/*-----------Main结束------------*/
void init_all(void)
{
	/*初始化所有*/
	SysInit();//初始化系统时钟与中断
	init_usart1(115200);//初始化串口1 串口屏（调试） PA9 PA10
	init_usart2(115200);//初始化串口2 扫码  PA2 PA3
	init_usart3(115200);//初始化串口3 openmv PB10 PB11
	init_uart4(115200);//初始化串口4 发数据给总控  PC10 PC11
//	W25QXX_Init();//初始化外部falsh
	//Goods_Init();//初始化商品信息
	Save_Goods_falsh();
	Save_user_falsh();
	//Init_User();//初始化用户信息
	Servo_Init();//舵机初始化
}

void RunAllTask(void)
{
	/*执行任务*/
	USART1_RecProcess();//处理串口屏发来的数据
	USART2_RecProcess();//处理扫码的数据
	USART3_RecProcess();//处理openmv的数据
	UART4_RecProcess();//处理上位机数据
	Task1();//判断是否开门
	Task2();//发送上传数据
}
