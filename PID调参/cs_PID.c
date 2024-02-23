#include "cs_pid.h"
#include "math.h"
#define INTEGRAL_MAX 1000
#define OUTPUTVAL_MAX 1000
PID R_PID;
PID L_PID;
void PID_Init(void)
{
    R_PID.P = 116;
    R_PID.I = 451;
    R_PID.D = 0;
    R_PID.error = 0;
    R_PID.integral = 0;
    R_PID.outPutVal = 0;
    R_PID.targetVal = 0;
    R_PID.oldError = 0;
    L_PID.P = 116;
    L_PID.I = 451;
    L_PID.D = 0;
    L_PID.error = 0;
    L_PID.integral = 0;
    L_PID.outPutVal = 0;
    L_PID.targetVal = 0;
    L_PID.oldError = 0;
}
void setPIDTargetVal(PID * pid,float val)
{
    pid->targetVal = val;
}
uint16_t getPlacePIDVal(float nowVal,PID *pid)
{
    if(nowVal < 0)
    {
        nowVal = -nowVal;
    }
    pid->error = pid->targetVal - nowVal;
   
    if (fabs(pid->integral) < INTEGRAL_MAX) 
    {
    pid->integral += pid->error;
    }
    pid->outPutVal += (uint16_t)(pid->P * pid->error + pid->I * pid->integral + pid->D * (pid->error - pid->oldError));
    pid->outPutVal = (pid->outPutVal > OUTPUTVAL_MAX) ? OUTPUTVAL_MAX : pid->outPutVal;
    pid->oldError = pid->error;
    return pid->outPutVal;
}
uint16_t getIncrementPIDVal(float nowVal,PID *pid)
{
    if(nowVal < 0)
    {
        nowVal = -nowVal;
    }
    pid->error = pid->targetVal - nowVal;
    pid->outPutVal += (float)(pid->P * (pid->error - pid->oldError)  + pid->I * pid->error);
    pid->outPutVal = (pid->outPutVal > OUTPUTVAL_MAX) ? OUTPUTVAL_MAX : pid->outPutVal;
    pid->oldError = pid->error;
    pid->outPutVal = pid->outPutVal < 0 ? 0: pid->outPutVal;
    return pid->outPutVal;
}



