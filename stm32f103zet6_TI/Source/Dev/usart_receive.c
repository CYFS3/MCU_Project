#include "usart_receive.h"
/*串口1数据接收*/
void USART1_Receive(u8 data[])
{
	
}
/*串口2数据接收*/
void USART2_Receive(u8 data[])
{
	
}
/*串口3数据接收*/
void USART3_Receive(u8 data[])
{
	
}
/*串口4数据接收(接收手机PID调参)*/
void UART4_Receive(u8 data[])
{
	if(strstr((const char*)data,"*PID_P,")!=NULL)
	{
		float P;
		sscanf((const char*)data,"*PID_P,%f",&P);
		PID_Adjust_P(&TrackPid,P);
		return;
	}
	if(strstr((const char*)data,"*PID_I,")!=NULL)
	{
		float I;
		sscanf((const char*)data,"*PID_I,%f",&I);
		PID_Adjust_I(&TrackPid,I);
		return;
	}
	if(strstr((const char*)data,"*PID_D,")!=NULL)
	{
		float D;
		sscanf((const char*)data,"*PID_D,%f",&D);
		PID_Adjust_P(&TrackPid,D);
		return;
	}
}
/*串口5数据接收(蓝牙无线PID调参)*/
void UART5_Receive(u8 data[])
{
	float P=0,I=0,D=0;
	sscanf((const char*)data,"#PID#%f,%f,%f#",&P,&I,&D);
	PID_Adjust(&TrackPid,P,I,D);//重新设定PID参数值
}
