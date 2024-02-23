#ifndef _ENCODER_H__
#define _ENCODER_H__
#include "config.h"

#define ENCODER_STARTER 30000
typedef enum WheelNumber {
		RIGHT_WHEEL = 2,  // 右轮
        LEFT_WHEEL= 3,      // 左轮
}WheelNumber;

extern float Car_Wheel_Speed[2];
extern float DistanceSum;
extern float Car_Speed;
void Init_Encoder(void);
void Encoder_Left_Front_TIM2Init(void);
void Encoder_Left_Back_TIM3Init(void);
void get_Car_All_Speed(void);
float GetCarSpeed(WheelNumber WHEEL);
#endif
