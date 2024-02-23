#ifndef ADC_H_
#define ADC_H_
#include "config.h"
#define LIGHT_PIN    GPIO_Pin_0
#define LIGHT_PORT   GPIOA
#define LIGHT_CHANNEL ADC_Channel_0

#define MQ_PIN       GPIO_Pin_1
#define MQ_PORT      GPIOA
#define MQ_CHANNEL   ADC_Channel_1

#define ADCx         ADC1
void adc1_init(void);
u16 Get_adc1(u8 channel);
u16 Get_Adc1_Average(u8 ch,u8 times);

#endif
