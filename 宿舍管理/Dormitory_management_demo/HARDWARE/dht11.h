#ifndef __DHT11_H
#define __DHT11_H
#include "stm32f10x.h"                  // Device header

extern unsigned int rec_data[4];

#define dht11_high GPIO_SetBits(GPIOA, GPIO_Pin_0)
#define dht11_low GPIO_ResetBits(GPIOA, GPIO_Pin_0)
#define Read_Data GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)

void DHT11_GPIO_Init_OUT(void);
void DHT11_GPIO_Init_IN(void);
void DHT11_Start(void);
unsigned char DHT11_REC_Byte(void);
void DHT11_REC_Data(void);


#endif

