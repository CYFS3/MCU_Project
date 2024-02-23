#include  "config.h"

void SysInit(void);



int main()
{
	SysInit();
    delay_Ms(100);
	
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
    delay_Ms(5000);
    printf("init esp8266");
    Esp8266_MQTT_Init();
    printf("init esp8266 ok");
    init_usart2(115200);
    DH11_OLED_Init();
    GPIO_ini();
    //舵机初始化
	TIME3Init(7199,199);
	
	//继电器初始化	
	relayInit();
    
	PcdReset();
	PcdAntennaOff(); 
	PcdAntennaOn();
	M500PcdConfigISOType( 'A' );
	//DHT11初始化
	DHT11_Start();
}
