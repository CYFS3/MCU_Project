#ifndef __SYSTICK_H__
#define __SYSTICK_H__
#include "config.h"

#define MAX_TIMER 8
extern  u32 sysTimer[MAX_TIMER];

#define DelayTimer sysTimer[0]
#define ATaskTimer sysTimer[1]
#define BTaskTimer sysTimer[2]
#define CTaskTimer sysTimer[3]
#define LCDTaskTimer sysTimer[4]
#define USART1RecTimer sysTimer[5]
#define USART2RecTimer sysTimer[6]
#define DTaskTimer sysTimer[7]
void SystickInit(void);
#endif


