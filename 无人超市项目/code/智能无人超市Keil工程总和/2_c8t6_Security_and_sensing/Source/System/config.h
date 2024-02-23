#ifndef _CONFIG_H_
#define _CONFIG_H_

/*宏定义布尔型变量*/
#define bool _Bool
#define true 1
#define false 0

/*C语言自带库*/
#include "stdio.h"
#include "string.h"
#include "math.h"

/* stm32标准库 */
#include "stm32f10x.h"

/* DEV库 */
#include "led.h"
#include "system.h"
#include "systick.h"
#include "usart.h"
#include "timer.h"
#include "adc.h"
#include "task.h"

/*CDH库*/
#include "cdh_fun_stm32.h"
#include "data_helper.h"

/*Sensor头文件*/
#include "dht11.h"
#include "light.h"
#include "fire.h"
#include "beep.h"
#include "smoke_MQ.h"
#include "big_led.h"
#include "fan.h"
/*USE*/
#include "to_main_zet6.h"

/*LCD*/
#include "lcd.h"
#include "lcd_init.h"
#include "sensor_lcd.h"
#endif
