#include "config.h"


void task_Run_One(void)
{
	if(ATaskTimer)return;
	ATaskTimer = AtaskPeriod;
    get_Car_All_Speed();
    printf("%f,%f,%f,%f,%f,%f,%f\r\n",R_PID.targetVal,Car_Wheel_Speed[0],R_PID.P,R_PID.I,R_PID.D,R_PID.error,(R_PID.outPutVal));
    Set_PWM_Right(getIncrementPIDVal(Car_Wheel_Speed[0],&R_PID));
    Set_PWM_Legh(getIncrementPIDVal(Car_Wheel_Speed[1],&L_PID));
	
}
void task_Run_Two(void)
{
	if(BTaskTimer)return;
	BTaskTimer = BtaskPeriod;
    CarControl();
}

void task_Run_Three(void)
{
	
}

void task_Run_All(void)
{
    task_Run_One();
    //task_Run_Two();
	USART1_RecProsess();
}
void TaskInit(void)
{
	//给个分任务定时值赋初值
	ATaskTimer = AtaskPeriod;
	BTaskTimer = BtaskPeriod;
	CTaskTimer = CtaskPeriod;
	USART1RecTimer = USART1RecPeriod;
}


