#ifndef _CAR_TB6612_H__
#define _CAR_TB6612_H__
#include "config.h"
void Init_TB6612(void);//初始化电机驱动
void Car_Control_Init(void);
void Car_Front(void);
void Car_Back(void);
void Car_Stop(void);
void Car_PWM_Init(void);
void Set_PWM_Compare1(uint16_t pulse);//左前轮
void Set_PWM_Compare2(uint16_t pulse);//左后轮
void Set_PWM_Compare3(uint16_t pulse);//右前轮
void Set_PWM_Compare4(uint16_t pulse);//右后轮

void Set_PWM_percent1(float duty_cycle);
void Set_PWM_percent2(float duty_cycle);
void Set_PWM_percent3(float duty_cycle);
void Set_PWM_percent4(float duty_cycle);

void BrakeCar(void);
void RestartCar(void);


#endif

