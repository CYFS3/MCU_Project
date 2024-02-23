#include "task.h"
/*分任务*/
const u32 ConstTaskTime[4]={150,200,200,200};//任务1、2、3、4执行时间间隔ms
/*任务1*/
void Task1(void)
{
	if(Task1Timer)return;
	Task1Timer=ConstTaskTime[0];
	//此处写任务要执行的代码
	UpdateWord();
}
bool is_EIC=1;
bool getEIC(void)
{
	return is_EIC;
}
void setEIC(bool EIC_state)
{
	is_EIC=EIC_state;
}
/*任务2*/
void Task2(void)
{
	if(Task2Timer)return;
	Task2Timer=ConstTaskTime[1];
	//此处写任务要执行的代码
		if(is_EIC)
	{
		if(get_pir())	
			open_door();
		else
			close_door();
	}
}

/*任务3*/
void Task3(void)
{
	if(Task3Timer)return;
	Task3Timer=ConstTaskTime[2];
	//此处写任务要执行的代码
	char updata[64];
	snprintf(updata,sizeof(updata),"<data.start>%d,%d<data.end>\r\n",getEIC(),isDoor_());
	usart_send_string(USART1,(u8*)updata);
}

/*任务4*/
void Task4(void)
{
	if(Task4Timer)return;
	Task4Timer=ConstTaskTime[3];
	//此处写任务要执行的代码
}
void pose(u8* data)
{
	if(strstr((const char*)data,"<data.start>"))
	{
		int eic,door;
		sscanf((const char *)data,"<command.start>%d,%d<command.end>",&eic,&door);
		setEIC(eic);
		if(door)
		{
			open_door();
		}else
		{
			close_door();
		}
	}
}
