#include "task.h"
/*分任务*/
static const u32 ConstTaskTime[5]={50,250,100,250,250};//任务1、2、3、4、5执行时间间隔

/*任务1(获取和校准传感器数据)*/
void Task1(void)
{
	if(Task1Timer)return;
	Task1Timer=ConstTaskTime[0];
	//此处写任务要执行的代码
	DHT11_Read_Data(&(data.temp),&(data.humi));//获取温湿度
	data.light=GetLightLux();//获取光照
	data.SmokeScope=GetSmokescope();//获取烟雾浓度
	data.is_fire=GetFireState();//获取火焰状态
	data.is_fan=GetFanState();//获取排风扇开关状态
	data.is_beep=GetBeepState();//获取蜂鸣器开关状态
	data.is_lamp=GetBigLedState();//获取大灯的开关状态
	data.is_EIC=GetEICState();//获取闭环控制是否开启
}

/*任务2 (串口1发送数据到电脑调试)*/
void Task2(void)
{
	if(Task2Timer)return;
	Task2Timer=ConstTaskTime[1];
	//此处写任务要执行的代码
	char message[256];
	snprintf(message,sizeof(message),
		"温度：%d℃ 湿度=%d%% 光照强度：%dLux 烟雾浓度PPM值：%.2f  是否有火焰=%c 排风扇开关=%c 蜂鸣器火灾报警=%c 超市灯开关=%c\r\n"
	,data.temp
	,data.humi
	,data.light
	,data.SmokeScope
	,data.is_fire?'1':'0'
	,data.is_fan?'1':'0'
	,data.is_beep?'1':'0'
	,data.is_lamp?'1':'0');
	usart_send_string(USART1,(u8*)message);
}

/*任务3(智能逻辑闭环控制)*/
bool is_EIC=true;//是否开启自动闭环控制
/*设置EIC状态*/
void SetEICState(bool eic_state)
{
	is_EIC=eic_state;
}
/*获取EIC状态*/
bool GetEICState(void)
{
	return is_EIC;
}
void Task3(void)
{
	if(Task3Timer)return;
	Task3Timer=ConstTaskTime[2];
	//此处写任务要执行的代码
	if(is_EIC)
	{
		SetBeepState((data.is_fire || data.SmokeScope>80) ? 1:0);//根据火焰与烟雾状态判断火灾检测报警
		SetBigLedState(data.light<100? 1:0);//根据光照强度判断并控制超市的灯是否开关
	}
}

/*任务4(LCD屏幕显示)*/
void Task4(void)
{
	if(Task4Timer)return;
	Task4Timer=ConstTaskTime[3];
	//此处写任务要执行的代码
	change_show_lcd();//在LCD屏幕上显示和更新各传感器数值
}

/*任务5(发送所有数据到ZET6总控制)*/
void Task5(void)
{
	if(Task5Timer)return;
	Task5Timer=ConstTaskTime[4];
	//此处写任务要执行的代码
	send_to_zet6();//发送所有数据到ZET6总控制
}
