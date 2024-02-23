#include "config.h"

void task_Run_One(void)
{
    //处理上位机数据
	if(ATaskTimer)return;
	ATaskTimer = AtaskPeriod;
    USART1_RecProcess();
    USART2_RecProcess();

	
}
void task_Run_Two(void)
{
	//处理灯的状态
    if(BTaskTimer)return;
	BTaskTimer = BtaskPeriod;
    if(switch_state == 0)
    {
        LED1_OFF();
    }
    else if(switch_state == 1)
    {
        LED1_ON();
    }
    if(sluice_state == 0)
    {
        water_OFF();
    }
    else if(sluice_state == 1)
    {
        water_ON();
    }
    
}

void task_Run_Three(void)
{
	 if(CTaskTimer)return;
    RC522_read_card();
	CTaskTimer = CtaskPeriod;
    if(rc_state.RC_OK == 1)
    {
        printf("OK ！！！");
        Door_open();
        MQTT_Send_Door_Open();
        rc_state.RC_OK = 2;
    }
    else if(rc_state.RC_OK == 2)
    {
        rc_state.RC_Timer++;
        if(rc_state.RC_Timer > 3)
        {
            Door_close();
            rc_state.RC_OK = 0;
            rc_state.RC_Timer = 0;
        }
    }
}
void task_Run_four(void)
{
    if(DTaskTimer)return;
	DTaskTimer = DtaskPeriod;
    DHT11_show();
    MQTT_Send_monitor(rec_data[2],rec_data[0]);
}

void task_Run_All(void)
{
	task_Run_One();
	task_Run_Two();
    task_Run_Three();
    task_Run_four();
}
void TaskInit(void)
{
	//给个分任务定时值赋初值
	ATaskTimer = AtaskPeriod;
	BTaskTimer = BtaskPeriod;
	CTaskTimer = CtaskPeriod;
    DTaskTimer = DtaskPeriod;
	USART1RecTimer = USART1RecPeriod;
}


