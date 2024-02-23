#ifndef _SYSTICK_H_
#define _SYSTICK_H_
#include "config.h"
#define MAX_TIMER 15
extern volatile u32 sysTimer[MAX_TIMER];
#define DelayTimer sysTimer[0]
#define USART1RecTimer sysTimer[1]
#define USART2RecTimer sysTimer[2]
#define USART3RecTimer sysTimer[3]
#define USART1RecProcessTimer sysTimer[4]
#define USART2RecProcessTimer sysTimer[5]
#define USART3RecProcessTimer sysTimer[6]

/*分任务定时器*/
#define Task1Timer sysTimer[7]
#define Task2Timer sysTimer[8]
#define Task3Timer sysTimer[9]
#define Task4Timer sysTimer[10]
#define Task5Timer sysTimer[11]

/*自定义用途系统定时器*/
#define Cust_Timer1 sysTimer[12]
#define Cust_Timer2 sysTimer[13]
#define Cust_Timer3 sysTimer[14]


void SystickInit(void);
void DelayMs(u32 nms);
void DelayUs(u32 nus);
#endif
