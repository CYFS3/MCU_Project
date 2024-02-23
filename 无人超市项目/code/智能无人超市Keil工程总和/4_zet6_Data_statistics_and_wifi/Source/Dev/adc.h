#ifndef ADC_H_
#define ADC_H_
#include "config.h"
void adc1_init(void);
u16 Get_adc1(u8 channel);
u16 Get_Adc1_Average(u8 ch,u8 times);

#endif
