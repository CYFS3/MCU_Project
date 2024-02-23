#include "uploading.h"

/*上传所有的反馈数据*/
void UploadFeedbackData(void)
{
	/*打包数据*/
	cJSON *root = cJSON_CreateObject();
	if(root)
	{
		/*数据类型*/
		cJSON_AddStringToObject(root, "data_type", "common_data");
		/*入门处*/
		cJSON_AddNumberToObject(root, "entrance_EIC", entrance_data_X.is_EIC);
		cJSON_AddNumberToObject(root, "entrance_door", entrance_data_X.is_door);
		/*传感器*/
		cJSON_AddNumberToObject(root, "sensor_EIC", sensor_data_X.is_EIC);
		cJSON_AddNumberToObject(root, "sensor_temp", sensor_data_X.temp);
		cJSON_AddNumberToObject(root, "sensor_humi", sensor_data_X.humi);
		cJSON_AddNumberToObject(root, "sensor_SmokeScope", sensor_data_X.SmokeScope);
		cJSON_AddNumberToObject(root, "sensor_light", sensor_data_X.light);
		cJSON_AddNumberToObject(root, "sensor_fire", sensor_data_X.is_fire);
		cJSON_AddNumberToObject(root, "sensor_lamp", sensor_data_X.is_lamp);
		cJSON_AddNumberToObject(root, "sensor_beep", sensor_data_X.is_beep);
		cJSON_AddNumberToObject(root, "sensor_fan", sensor_data_X.is_fan);
		/*扫码处*/
		cJSON_AddNumberToObject(root, "scancode_EIC", con_data_X.is_EIC);
		cJSON_AddNumberToObject(root, "scancode_door", con_data_X.is_door);
		/*打包数据*/
		char *app_data_str = cJSON_Print(root);
		usart_send_string(USART_Wifi, (u8 *)app_data_str);
		cJSON_free(app_data_str);
		/*释放内存*/
		cJSON_Delete(root);
	}
}

/*上传订单数据*/
void upload_indent_data(void)
{
		cJSON *root = cJSON_CreateObject();
		if(root)
		{
			cJSON_AddStringToObject(root, "data_type", "indent_data");
			cJSON_AddNumberToObject(root, "user_id", indent_data_X.UserID);
			cJSON_AddNumberToObject(root, "data_num", indent_data_X.CountNum);
			cJSON *GoodsIdList = cJSON_CreateArray();
			for(int i=0;i<indent_data_X.CountNum;i++)
			{//商品ID
				cJSON_AddItemToArray(GoodsIdList, cJSON_CreateNumber(indent_data_X.GoodsIdList[i]));
			}
			cJSON_AddItemToObject(root, "GoodsIdList", GoodsIdList);
			cJSON *GoodsNumberList = cJSON_CreateArray();
			for(int i=0;i<indent_data_X.CountNum;i++)
			{//单个商品数量
				cJSON_AddItemToArray(GoodsNumberList, cJSON_CreateNumber(indent_data_X.GoodsNumList[i]));
			}
			cJSON_AddItemToObject(root, "GoodsNumberList", GoodsNumberList);
			cJSON_AddNumberToObject(root, "discount", indent_data_X.discount);
			char *indent_data_str = cJSON_Print(root);
			usart_send_string(USART_Wifi, (u8 *)indent_data_str);
			cJSON_free(indent_data_str);
			cJSON_Delete(root);
		}
}