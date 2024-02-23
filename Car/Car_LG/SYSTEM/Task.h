#ifndef __TASK_H__
#define __TASK_H__

#define AtaskPeriod 100	//A任务周期
#define BtaskPeriod 150	//B任务周期
#define CtaskPeriod 200
#define USART1RecPeriod 10
#define USART1RecTimerPeriod 10
void task_Run_One(void);
void task_Run_Two(void);
void task_Run_Three(void);
void task_Run_All(void);
void TaskInit(void);


#endif
