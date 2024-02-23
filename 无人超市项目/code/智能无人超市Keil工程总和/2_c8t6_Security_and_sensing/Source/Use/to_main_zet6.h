#ifndef TO_MAIN_ZET6
#define TO_MAIN_ZET6
#include "config.h"
typedef struct
{
	u8 temp,humi;//温湿度
	float SmokeScope;//烟雾浓度
	u32 light;//光照强度
	bool is_fire;//有没有火
	bool is_lamp;//灯的亮灭
	bool is_beep;//蜂鸣器
	bool is_fan;//排气扇
	bool is_EIC;//是否开启闭环逻辑控制
}SensorData;
extern SensorData data;
void send_to_zet6(void);
void init_data(void);
void DealWithCommand(u8 *message);
#endif
