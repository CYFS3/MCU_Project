#include "Car_Control.h"
#define TARGETVAL_BASE 0.3
u8 time = 0;
void timeAdd(void)
{
    if(time <= 20)
    {
        time++;
    }
}
char control;
void CarControl(void)
{
        if(Length(&queue) != 0)
        {
           control = DeQueue(&queue);
        }
        switch (control)
        {
            case 'A':
                Car_Left();
                setPIDTargetVal(&R_PID,0.3);
                setPIDTargetVal(&L_PID,0);
                break;
            case 'S':
                Car_Back();
                timeAdd();
                setPIDTargetVal(&R_PID,TARGETVAL_BASE + time * 0.015);
                setPIDTargetVal(&L_PID,TARGETVAL_BASE + time * 0.015);
                break;
            case 'D':
                Car_Right();
                setPIDTargetVal(&R_PID,0);
                setPIDTargetVal(&L_PID,0.3);
                break;
            case 'W':
                Car_Front();
                timeAdd();
                setPIDTargetVal(&R_PID,TARGETVAL_BASE + time * 0.015);
                setPIDTargetVal(&L_PID,TARGETVAL_BASE + time * 0.015);
                break;
            default:
                Car_Stop();
                setPIDTargetVal(&R_PID,0);
                setPIDTargetVal(&L_PID,0);
                time = 0;
                break;
        }
    
}

