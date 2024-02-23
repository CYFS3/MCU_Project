

#include "systick.h"

u32 sysTimer[MAX_TIMER];


void SystickInit(void)
{
	for(u8 i=0;i<MAX_TIMER;i++)
	{//对任务数组初始值清0
		sysTimer[i]=0;
	}	
	SysTick_Config(72000000/1000);//设置滴答定时器1ms

}



void SysTick_Handler(void)
{
	//每1ms定时值到，会进一次
	for(u8 i=0;i<MAX_TIMER;i++)
	{
		if(sysTimer[i])
		{
			sysTimer[i]--;	
		}
	}
}
