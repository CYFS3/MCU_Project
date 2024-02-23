#include  "config.h"

void SysInit(void);

int main()
{
	SysInit();
    
	
	while(1)
	{
		task_Run_All();
	}
}


void SysInit(void)
{
	CPU_INT_ENABLE();//开总中断
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级
	SystickInit();//滴答时钟初始化
	TaskInit();
    init_usart1(115200);
    //等待ESP8266WIFI连接
    delay_Ms(3000);
    //ESP8266 MQTT初始化
    printf("init esp8266");
    Esp8266_MQTT_Init();
    printf("init esp8266 ok");   
    LCD_Init();//LCD初始化   
    RC522Init(); //RC522初始化  
	TIME3Init(7199,199);//舵机初始化	
	relayInit();//继电器初始化		
	DHT11_Start();//DHT11初始化
}
