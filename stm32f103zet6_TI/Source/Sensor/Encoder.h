#ifndef _ENCODER_H__
#define _ENCODER_H__
#include "config.h"

#define ENCODER_STARTER 30000
typedef enum WheelNumber {
		LEFT_FRONT_WHEEL = 2,  // 左前轮
    LEFT_BACK_WHEEL= 3,      // 左后轮
    RIGHT_FRONT_WHEEL= 4,      // 右前轮
    RIGHT_BACK_WHEEL = 5       // 右后轮
}WheelNumber;

extern float Car_Wheel_Speed[4];
extern float DistanceSum;
extern float Car_Speed;
void Init_Encoder(void);
void Encoder_Left_Front_TIM2Init(void);
void Encoder_Left_Back_TIM3Init(void);
void Encoder_Right_Front_TIM4Init(void);
void Encoder_Right_Back_TIM5Init(void);
void get_Car_All_Speed(void);
float GetCarSpeed(WheelNumber WHEEL);
#endif
