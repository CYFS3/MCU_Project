#ifndef _CAR_TB6612_H__
#define _CAR_TB6612_H__
#include "config.h"
void Init_TB6612(void);//初始化电机驱动
void Car_Control_Init(void);
void Car_Front(void);
void Car_Back(void);
void Car_Left(void);
void Car_Right(void);
void Car_Left_Whirl(void);
void Car_Right_Whirl(void);
void Car_Stop(void);
void Car_PWM_Init(void);

void Set_PWM_Right(uint16_t duty_cycle);
void Set_PWM_Legh(uint16_t duty_cycle);

#endif

