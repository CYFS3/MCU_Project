#include "task.h"
#include "Openmv.h"
/*分任务*/
const u32 ConstTaskTime[4]={3000,200,200,200};//任务1、2、3、4执行时间间隔

/*任务1 正常逻辑*/
void Task1(void)
{
	if(Task1Timer)return;
	Task1Timer=ConstTaskTime[0];
	if(is_EIC)
	{
		if(is_door)
		{
			Door_ON();
			is_door=false;
		}else
		{
			Door_OFF();
		}
	}
}

/*任务2*/
void Task2(void)
{
	if(Task2Timer)return;
	Task2Timer=ConstTaskTime[1];
	//此处写任务要执行的代码
	update_code();
	printf("11");
}

/*任务3*/
void Task3(void)
{
	if(Task3Timer)return;
	Task3Timer=ConstTaskTime[2];
	//此处写任务要执行的代码
	
}

/*任务4*/
void Task4(void)
{
	if(Task4Timer)return;
	Task4Timer=ConstTaskTime[3];
	//此处写任务要执行的代码
	
}
