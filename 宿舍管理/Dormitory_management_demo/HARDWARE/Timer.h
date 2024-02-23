#ifndef __TIMER_H
#define __TIMER_H

#include "config.h"
void TIME3Init(u16 PSC,u16 ARR);
void TIM2_Int_Init(u16 arr,u16 psc);
void TIM4_Int_Init(u16 arr,u16 psc);
#endif



