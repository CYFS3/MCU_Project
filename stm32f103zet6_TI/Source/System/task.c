#include "task.h"
const int ConstTasktimers[4]={0,200,200,0};
/*任务1*/
void Task1(void)
{
	if(Task1Timer)return;
	Task1Timer=ConstTasktimers[0];
	Track();//循迹
}

/*任务2*/
void Task2(void)
{
	if(Task2Timer)return;
	Task2Timer=ConstTasktimers[1];
	
}

/*任务3*/
void Task3(void)
{
	if(Task3Timer)return;
	Task3Timer=ConstTasktimers[1];
	
}

/*任务4 串口接收任务*/
void Task4(void)
{
	if(Task4Timer)return;
	Task4Timer=ConstTasktimers[1];
	USART1_RecProcess();
	USART2_RecProcess();
	USART3_RecProcess();
	UART4_RecProcess();
	UART5_RecProcess();
}
