#ifndef __CONFIG_H__
#define __CONFIG_H__
#define CPU_INT_ENABLE() {__set_PRIMASK(0);}//开总中断开关
#define CPU_INT_DISABLE() {__set_PRIMASK(1);}//关总中断开关
/*宏定义布尔型变量*/
#define bool _Bool
#define true 1
#define false 0

/*C语言自带库*/
#include "stdio.h"
#include "string.h"
#include <stdint.h>
#include <stdlib.h>

/* stm32标准库 */
#include "stm32f10x.h"

/*系统库*/
#include "RemapGPIO.h"
#include "systick.h"
#include "Delay.h"
#include "Task.h"

/*外设库*/
#include "GPIO.h"
#include "usart.h"
#include "mqtt_esp8266.h"
#include "CJSON.h"
#include "oled_iic.h"
#include "RC522.h"
#include "Hanshu.h"
#include  "dht11.h"
#include "relay.h"
#include "Timer.h"


#endif
