#ifndef _DATA_RECEIVE_H_
#define _DATA_RECEIVE_H_
#include "config.h"

typedef struct
{//入口处控制
	int is_EIC,is_door;//EIC控制 
}DATA_Entrance;
typedef struct
{//传感器数据
	int temp,humi;//温湿度
	float SmokeScope;//烟雾浓度
	u32 light;//光照强度
	int is_fire;//有没有火
	int is_lamp;//灯的亮灭
	int is_beep;//蜂鸣器
	int is_fan;//排气扇
	int is_EIC;//是否开启闭环逻辑控制
}DATA_SensorSafe;
typedef struct
{//控制扫码部分
	int is_EIC,is_door;
}DATA_ScanCode_Con;
typedef struct
{//商品
	u32 ID;
	u8 *GoodsBarCode;
	u8 *GoodsName;
	float price;
}DATA_ScanCode_Goods;

//订单
typedef struct
{
	u32 UserID;//用户ID
	u32 CountNum;//结算的商品种类总数
	u32 GoodsIdList[100];//商品ID列表
	u32 GoodsNumList[100];//商品单类数量
	float discount;//折扣
}DATA_Indent;
void receive_Entrance(u8 *data);
void receive_Sensor(u8 *data);
void receive_ScanCode(u8 *data);
void receive_App(u8 *data);

void init_all_data(void);
int ParseIndent_string(const char *str, DATA_Indent *indent);
extern DATA_Indent indent_data_X;
extern DATA_Entrance entrance_data_X;//上传的门的状态和EIC状态(超市入门)
extern DATA_SensorSafe sensor_data_X;//上传的各传感器数据(超市中间)
extern DATA_Indent indent_data_X;//上传的订单信息(超市结算)
extern DATA_ScanCode_Con con_data_X;//上传的超市后门状态(超市结算)
#endif
