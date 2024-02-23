#include "cs_vofa.h"
#define CMD_MAX 10
char cmd[CMD_MAX];
float parameter;

void messageSetPID(char * str)
{
    if(sscanf(str,"%4s%f",cmd,&parameter) != 2) return;
    if(cmd[0] == 'R')
    {
        if(cmd[1] != '_' || cmd[3] != '=') return;
        if(cmd[2] == 'P')
        {
            R_PID.P = parameter;
        }
        else if(cmd[2] == 'I')
        {
            R_PID.I= parameter;
        }
        else if(cmd[2] == 'D')
        {
            R_PID.D= parameter;
        }
        else if(cmd[2] == 'T')
        {
            R_PID.targetVal = parameter;
        }
    }
    else if(cmd[0] == 'L')
    {
       if(cmd[1] != '_' || cmd[3] != '=') return;
        if(cmd[2] == 'P')
        {
            L_PID.P = parameter;
        }
        else if(cmd[2] == 'I')
        {
            L_PID.I= parameter;
        }
        else if(cmd[2] == 'D')
        {
            L_PID.D= parameter;
        } 
        else if(cmd[2] == 'T')
        {
            L_PID.targetVal = parameter;
        }
    }
}

