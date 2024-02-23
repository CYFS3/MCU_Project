#include "command.h"

/*发送信息到调试串口*/
void SendMessageTo_PC(char *message)
{
	usart_send_string(USART_PC,(u8*)message);
}

/*超市入口处
*@参数1:开关EIC逻辑闭环控制
*@参数2:开关超市入口大门
*/
void SendCommandTo_entrance(bool is_EIC,bool is_door)
{
	char command_str[128];//128位数据
	snprintf(command_str, sizeof(command_str),"<command.start>%d,%d<command.end>\r\n",is_EIC,is_door);
	usart_send_string(USART_entrance,(u8 *)command_str);
}

/*超市安全与传感器
*@参数1:开关EIC逻辑闭环控制
*@参数2:开关超市大灯
*@参数3:开关蜂鸣器火灾报警
*@参数4:开关超市排气扇
*/
void SendCommandTo_Security_and_sensing(bool is_EIC,bool is_lamp,bool is_beep,bool is_fan)
{
	char command_str[128];//128位数据
	snprintf(command_str, sizeof(command_str),"<command.start>%d,%d,%d,%d<command.end>\r\n",is_EIC,is_lamp,is_beep,is_fan);
	usart_send_string(USART_SensorSafe, (u8 *)command_str);
}

/*扫码付款核心
*@参数1:EIC
*@参数2:开关超市出口门
*@参数3:设置折扣
*/
void SendCommandTo_ScanCode(bool is_EIC,bool is_door,float discount)
{
	/*打包数据*/
	cJSON *root = cJSON_CreateObject();
	if(root)
	{
		cJSON_AddStringToObject(root, "data_type", "common_data");
		cJSON_AddNumberToObject(root, "scancode_EIC", is_EIC);
		cJSON_AddNumberToObject(root, "scancode_door", is_door);
		cJSON_AddNumberToObject(root, "scancode_discount", discount);
		/*打包数据*/
		char *app_data_str = cJSON_Print(root);
		usart_send_string(USART_ScanCode, (u8 *)app_data_str);
		cJSON_free(app_data_str);
		/*释放内存*/
		cJSON_Delete(root);
	}
}

/*扫码付款核心 (添加商品)
*@参数1:内部ID
*@参数2:条形码
*@参数3:商品名字
*@参数4:商品单价
*/
void SendCommandTo_ScanCode_Add_Goods(u32 ID,const char *GoodsBarCode,const char *GoodsName,float price)
{
	/*打包数据*/
	cJSON *root = cJSON_CreateObject();
	if(root)
	{
		cJSON_AddStringToObject(root, "data_type", "goods_data");
		cJSON_AddNumberToObject(root, "goods_id", ID);
		cJSON_AddStringToObject(root, "goods_name", GoodsName);
		cJSON_AddStringToObject(root, "goods_barcode", GoodsBarCode);
		cJSON_AddNumberToObject(root, "goods_price", price);
		/*打包数据*/
		char *app_data_str = cJSON_Print(root);
		usart_send_string(USART_ScanCode, (u8 *)app_data_str);
		cJSON_free(app_data_str);
		/*释放内存*/
		cJSON_Delete(root);
	}
}
