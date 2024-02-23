#ifndef __SYSTICK_H__
#define __SYSTICK_H__
#include "config.h"

#define MAX_TIMER 7
extern  u32 sysTimer[MAX_TIMER];

#define DelayTimer sysTimer[0]
#define ATaskTimer sysTimer[1]
#define BTaskTimer sysTimer[2]
#define CTaskTimer sysTimer[3]
#define USART1RecTimer sysTimer[4]
#define USART2RecTimer sysTimer[5]


void SystickInit(void);
#endif


