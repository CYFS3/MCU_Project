#ifndef _CONFIG_H_
#define _CONFIG_H_

/*宏定义布尔型变量*/
#define bool _Bool
#define true 1
#define false 0

/*C语言自带库*/
#include "stdio.h"
#include "string.h"
#include <stdint.h>
#include <stdlib.h>

#include "cJSON.h"
/* stm32标准库 */
#include "stm32f10x.h"

/* DEV库 */
#include "led.h"
#include "system.h"
#include "systick.h"

#include "timer.h"
#include "usart.h"
#include "adc.h"
#include "task.h"

/*CDH库*/
#include "cdh_fun_stm32.h"
#include "data_helper.h"

/*USE*/
#include "command.h"
#include "data_receive.h"
#include "uploading.h"
#include "wifi.h"
#endif
