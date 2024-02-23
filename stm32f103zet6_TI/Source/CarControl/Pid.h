#ifndef _PID_H_
#define _PID_H_
#include "config.h"
typedef struct
{
	float setpoint;  //设定值
	float kp, ki, kd;  //PID 参数
	float pre_error;  //上一次的误差
	float integral;  //积分值
}PID;
extern PID TrackPid;//循迹PID控制器
void PID_Init(PID *pid, float setpoint, float kp, float ki, float kd);
float PID_Compute(PID *pid, float input);

void PID_Adjust(PID *pid, float kp, float ki, float kd);
void Send_PID(PID *pid,u8 Mode);
void Set_Track_PID(float PID_Error,float Pulse_Offset);
void PID_Adjust_P(PID *pid, float kp);
void PID_Adjust_I(PID *pid, float ki);
void PID_Adjust_D(PID *pid, float kd);
#endif
