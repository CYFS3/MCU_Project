#include "data_receive.h"

/*从下位机接收的数据 -》app*/
DATA_Entrance entrance_data_X;//上传的门的状态和EIC状态(超市入门)
DATA_SensorSafe sensor_data_X;//上传的各传感器数据(超市中间)
DATA_Indent indent_data_X;//上传的订单信息(超市结算)
DATA_ScanCode_Con con_data_X;//上传的超市后门状态(超市结算)

/*初始化所有数据*/
void init_all_data(void)
{
	entrance_data_X.is_EIC=0;
	entrance_data_X.is_door=0;
	sensor_data_X.humi=0;
	sensor_data_X.is_beep=0;
	sensor_data_X.is_EIC=0;
	sensor_data_X.is_fan=0;
	sensor_data_X.is_fire=0;
	sensor_data_X.is_lamp=0;
	sensor_data_X.light=0;
	sensor_data_X.SmokeScope=0;
	sensor_data_X.temp=0;
	//订单不需要初始化因为不一直发
	con_data_X.is_door=0;
	con_data_X.is_EIC=0;
}
/*1处理(超市入口处)发来的数据*/
void receive_Entrance(u8 *data)
{
	//<data.start>EIC控制开关,门是否打开<data.end>0........................................
	sscanf((const char*)data,"<data.start>%d,%d<data.end>\r\n",&(entrance_data_X.is_EIC),&(entrance_data_X.is_door));
}

/*2处理传感器(超市中间)发来的数据*/
void receive_Sensor(u8 *data)
{
	//<data.start>%d,%d,%.2f,%d,%d,%d,%d,%d,%d<data.end>
	sscanf((const char*)data,"<data.start>%d,%d,%f,%d,%d,%d,%d,%d,%d<data.end>\r\n",
	&(sensor_data_X.temp),
	&(sensor_data_X.humi),
	&(sensor_data_X.SmokeScope),
	&(sensor_data_X.light),
	&(sensor_data_X.is_fire),
	&(sensor_data_X.is_lamp),
	&(sensor_data_X.is_beep),
	&(sensor_data_X.is_fan),
	&(sensor_data_X.is_EIC)
	);
}

/*3处理扫码核心单片机(超市结算处)发来的数据*/
void receive_ScanCode(u8 *data)
{
	if(strstr((const char *)data,"<indent.start>"))//接收订单信息解析存入并单独执行订单信息上传
	{
		if(!ParseIndent_string((const char *)data,&indent_data_X))
		{
			upload_indent_data();//订单信息上传到app
			SendMessageTo_PC("本次订单信息上传成功!");
		}else SendMessageTo_PC("订单信息解析错误!");
	}else
	{
		cJSON *root = cJSON_Parse((const char *)data);//接收扫码处数据反馈
		if(root!=NULL)
		{
			cJSON *scancode_EIC = cJSON_GetObjectItem(root,"scancode_EIC");
			cJSON *scancode_door = cJSON_GetObjectItem(root,"scancode_door");
			if(scancode_EIC!=NULL && scancode_door!=NULL)
			{
				con_data_X.is_EIC=scancode_EIC->valueint;
				con_data_X.is_door=scancode_door->valueint;
			}
			cJSON_Delete(root);
		}
	}
}

/*处理WIFI(APP上位机)发来的数据*/
void receive_App(u8 *data)
{
	cJSON *root = cJSON_Parse((const char*)data);
	if (root != NULL) 
	{
		/*入口处*/
		cJSON *entrance_EIC = cJSON_GetObjectItem(root, "entrance_EIC");
		cJSON *entrance_door_state = cJSON_GetObjectItem(root, "entrance_door");
		/*传感器处*/
		cJSON *sensor_EIC = cJSON_GetObjectItem(root, "sensor_EIC");
		cJSON *sensor_beep = cJSON_GetObjectItem(root, "sensor_beep");
		cJSON *sensor_lamp = cJSON_GetObjectItem(root, "sensor_lamp");
		cJSON *sensor_fan = cJSON_GetObjectItem(root, "sensor_fan");
		/*扫码处*/
		cJSON *scancode_EIC = cJSON_GetObjectItem(root, "scancode_EIC");
		cJSON *scancode_door = cJSON_GetObjectItem(root, "scancode_door");
		cJSON *scancode_discount = cJSON_GetObjectItem(root, "scancode_discount");
		/*添加商品处*/
		cJSON *goods_id = cJSON_GetObjectItem(root, "goods_id");
		cJSON *goods_barcode = cJSON_GetObjectItem(root, "goods_barcode");
		cJSON *goods_name = cJSON_GetObjectItem(root, "goods_name");
		cJSON *goods_price = cJSON_GetObjectItem(root, "goods_price");
		if(entrance_EIC&&entrance_door_state)
		{
			SendCommandTo_entrance(entrance_EIC->valueint,entrance_door_state->valueint);//发送命令入口处
		}
		if(sensor_EIC && sensor_beep  && sensor_lamp  && sensor_fan)
		{
			SendCommandTo_Security_and_sensing(sensor_EIC->valueint,sensor_beep->valueint,sensor_lamp->valueint,sensor_fan->valueint);//发送命令传感器处
		}
		if (scancode_EIC && scancode_door  && scancode_discount) 
		{
			SendCommandTo_ScanCode(scancode_EIC->valueint,scancode_door->valueint,(float)(scancode_discount->valuedouble));//发送命令到扫码处
		}
		if(goods_id!=NULL &&goods_barcode!=NULL&&goods_name!=NULL&&goods_price!=NULL)
		{//添加商品指令
			char BarName[36],Name[36];
			strcpy(BarName, goods_barcode->valuestring);
			strcpy(Name, goods_name->valuestring);
			SendCommandTo_ScanCode_Add_Goods(goods_id->valueint,BarName,Name,(float)(goods_price->valuedouble));//发送添加商品命令到扫码处
		}
		cJSON_Delete(root);
	}
}

/*解析订单字符串数据*/
int ParseIndent_string(const char *str, DATA_Indent *indent)
{
	  //<indent.start>[user_id]123456[data_num]3[GoodsIdList->]1,3,4[GoodsNumberList->]10,12,5[discount]0.75<indent.end>
    const char *tags[] = {"[user_id]", "[data_num]", "[GoodsIdList->]", "[GoodsNumberList->]", "[discount]", "<indent.end>"};
    const char *start = str;
    for (int i=0; i<6;i++) 
		{
        start = strstr(start, tags[i]);
        if (!start) return -1;
        start += strlen(tags[i]);
        if (i==0) indent->UserID = (u32)strtoul(start, (char **)&start, 10);
        else if (i==1) indent->CountNum = (u32)strtoul(start, (char **)&start, 10);
        else if (i==2) 
				{
					for (u32 j = 0; j < indent->CountNum; j++) 
					{
						indent->GoodsIdList[j] = (u32)strtoul(start, (char **)&start, 10);
						if (j<indent->CountNum-1) 
						{
							if (*start!=',') return -1;
							start++;
						}
					}
        }else if(i==3) 
				{
					for (u32 j = 0; j < indent->CountNum; j++) 
					{
						indent->GoodsNumList[j] = (u32)strtoul(start, (char **)&start, 10);
						if (j < indent->CountNum - 1) 
						{
								if (*start != ',') return -1;
								start++;
						}
          }
        }else{
            sscanf(start, "%f", &indent->discount);
            start = strstr(start, "<indent.end>");
        }
    }
    return 0;
}
