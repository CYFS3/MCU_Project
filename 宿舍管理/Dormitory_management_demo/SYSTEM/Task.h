#ifndef __TASK_H__
#define __TASK_H__

#define AtaskPeriod 10	//A任务周期
#define BtaskPeriod 500	//B任务周期
#define CtaskPeriod 500
#define DtaskPeriod 1000

#define ButtontaskPeriod 10 //按键任务周期
#define USART1RecPeriod 10
void task_Run_One(void);
void task_Run_Two(void);
void task_Run_Three(void);
void task_Run_All(void);
void TaskInit(void);


#endif
