#ifndef __CS_PID_H__
#define __CS_PID_H__
#include "config.h"

typedef struct
{
    float targetVal;//目标值
    float error;//误差
    float oldError;
    
    float P;
    float I;
    float D;
    
    
    float integral;//积分项
    float outPutVal;//输出
}PID;

extern PID R_PID;
extern PID L_PID;
void PID_Init(void);
uint16_t getIncrementPIDVal(float nowVal,PID* pid);
uint16_t getPlacePIDVal(float nowVal,PID* pid);
void setPIDTargetVal(PID * pid,float val);

#endif



