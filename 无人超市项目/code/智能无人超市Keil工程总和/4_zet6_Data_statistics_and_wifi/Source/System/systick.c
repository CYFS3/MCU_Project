#include "systick.h"
volatile u32 sysTimer[MAX_TIMER];//系统定时器(全局 需防代码优化)
/*设置系统中断周期并初始化系统定时器*/
void SystickInit(void)
{
	u8 i=0;
	for(i=0;i<MAX_TIMER;i++)sysTimer[i]=0;
	SysTick_Config(72000000/1000);
}

/*延时函数毫秒级*/
void DelayMs(u32 nms)
{
	DelayTimer=nms;
	while(DelayTimer);
}
/*延时函数微秒级*/
void DelayUs(u32 nus)
{
	u32 delta;
	u32 current_delay;
	nus = nus*(SysTick->LOAD/1000);
	delta=SysTick->VAL;
	do
	{
		if(delta > SysTick->VAL)current_delay=delta-SysTick->VAL;
		else current_delay=SysTick->LOAD + delta -	SysTick->VAL;
	}
	while(current_delay < nus);
}
/*系统中断函数*/
void SysTick_Handler(void)
{
	u8 i=0;
	for(i=0;i<MAX_TIMER;i++)
	{
	   if(sysTimer[i])sysTimer[i]--;
	 }
}
