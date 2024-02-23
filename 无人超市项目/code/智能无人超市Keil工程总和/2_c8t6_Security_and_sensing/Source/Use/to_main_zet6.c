#include "to_main_zet6.h"
SensorData data;//总传感器数据

/*发送所有数据到总控制(USART2)*/
void send_to_zet6(void)
{
	char data_str[128];//128位数据
	snprintf(data_str, sizeof(data_str),
		"<data.start>%d,%d,%.2f,%d,%d,%d,%d,%d,%d<data.end>\r\n",
		data.temp,
		data.humi,
		data.SmokeScope,
		data.light,
		data.is_fire ? 1 : 0,
		data.is_lamp ? 1 : 0,
		data.is_beep ? 1 : 0,
		data.is_fan ? 1 : 0,
		data.is_EIC ? 1 : 0);
	usart_send_string(USART2, (u8 *)data_str);
}
/*处理命令*/
void DealWithCommand(u8 *str)//<command.start>0,1,1,1<command.end>\r\n
{
	bool data_bool_list[4];
	char* start_ptr = strstr((char*)str, "<command.start>");
	char* end_ptr = strstr((char*)str, "<command.end>");
	if(start_ptr != NULL && end_ptr != NULL)//解析命令字符串
	{
		start_ptr += strlen("<command.start>");
		int data_len = end_ptr - start_ptr;
		char data_str[data_len + 1];
		strncpy(data_str, start_ptr, data_len);
		data_str[data_len] = '\0';
		int data_list[4];
		char* token = strtok(data_str, ",");
		int i = 0;
		while (token != NULL && i < 4)
		{
			data_list[i++] = strtol(token, NULL, 10);
			token = strtok(NULL, ",");
		}
		for (int j = 0; j < 4; j++)
		{
			data_bool_list[j] = (data_list[j] != 0);
		}
		SetEICState(data_bool_list[0]);//设置EIC流程
		SetBigLedState(data_bool_list[1]);//设置灯的状态
		SetBeepState(data_bool_list[2]);//设置蜂鸣器报警状态
		SetFanState(data_bool_list[3]);//设置排风扇状态
	}
}
/*初始化所有数据*/
void init_data(void)
{
	data.temp=0;
	data.humi=0;
	data.light=0;
	data.SmokeScope=0.0f;
	data.is_fire=0;
	data.is_lamp=GetBigLedState();
	data.is_beep=GetBeepState();
	data.is_fan=GetFanState();
	data.is_EIC=GetEICState();
}
