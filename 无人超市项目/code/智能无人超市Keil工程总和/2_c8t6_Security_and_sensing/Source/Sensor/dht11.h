#ifndef __DHT11_H
#define __DHT11_H  
#include "config.h"
////IO操作函数											   
#define	DHT11_DQ_OUT_0 GPIO_ResetBits(GPIOB,GPIO_Pin_8); //拉低数据端口	PA15 
#define	DHT11_DQ_OUT_1 GPIO_SetBits(GPIOB,GPIO_Pin_8); //拉高数据端口	PA15 

#define DHT11_GPIO_PORT    	GPIOB			              //GPIO端口
#define DHT11_GPIO_CLK 	    RCC_APB2Periph_GPIOB		//GPIO端口时钟
#define DHT11_GPIO_PIN		GPIO_Pin_8			        //连接到SCL时钟线的GPIO

typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned  int u32;

u8 DHT11_Init(void);//初始化DHT11
u8 DHT11_Read_Data(u8 *temp,u8 *humi);//读取温湿度
u8 DHT11_Read_Byte(void);//读出一个字节
u8 DHT11_Read_Bit(void);//读出一个位
u8 DHT11_Check(void);//检测是否存在DHT11
void DHT11_Rst(void);//复位DHT11    
#endif
