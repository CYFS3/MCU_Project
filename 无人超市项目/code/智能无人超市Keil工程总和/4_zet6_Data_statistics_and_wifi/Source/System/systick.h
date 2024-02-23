#ifndef _SYSTICK_H_
#define _SYSTICK_H_
#include "config.h"
#define MAX_TIMER 18
extern volatile u32 sysTimer[MAX_TIMER];
#define DelayTimer sysTimer[0]
#define USART1RecTimer sysTimer[1]
#define USART2RecTimer sysTimer[2]
#define USART3RecTimer sysTimer[3]
#define UART4RecTimer sysTimer[4]
#define UART5RecTimer sysTimer[5]

#define USART1RecProcessTimer sysTimer[6]
#define USART2RecProcessTimer sysTimer[7]
#define USART3RecProcessTimer sysTimer[8]
#define UART4RecProcessTimer sysTimer[9]
#define UART5RecProcessTimer sysTimer[10]

/*分任务定时器*/
#define Task1Timer sysTimer[11]
#define Task2Timer sysTimer[12]
#define Task3Timer sysTimer[13]
#define Task4Timer sysTimer[14]

/*自定义用途系统定时器*/
#define Cust_Timer1 sysTimer[15]
#define Cust_Timer2 sysTimer[16]
#define Cust_Timer3 sysTimer[17]


void SystickInit(void);
void DelayMs(u32 nms);
void DelayUs(u32 nus);
#endif
