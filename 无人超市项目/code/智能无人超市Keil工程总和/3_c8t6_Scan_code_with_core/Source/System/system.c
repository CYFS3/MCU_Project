#include "system.h"

void SysInit(void)
{
	__set_PRIMASK(0);//cpu中断启用
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断分组
	SystickInit();//初始化系统滴答时钟
}
