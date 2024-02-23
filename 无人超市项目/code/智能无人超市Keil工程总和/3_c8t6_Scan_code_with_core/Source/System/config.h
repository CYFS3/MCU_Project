#ifndef _CONFIG_H_
#define _CONFIG_H_

/*宏定义布尔型变量*/
#define bool _Bool
#define true 1
#define false 0

/*C语言自带库*/
#include "stdio.h"
#include "string.h"

/* stm32标准库 */
#include "stm32f10x.h"

/* DEV库 */
#include "system.h"
#include "systick.h"
#include "usart.h"
#include "timer.h"
#include "adc.h"
#include "task.h"
#include "RemapGPIO.h"

/*DataGoods库*/
#include "Goods.h"
#include "User.h"

/*Payment库*/

#include "Openmv.h"
#include "spi.h"
#include "w25qxx.h"
#include "Usarttft.h"
#include "Servo.h"
#include "ScanCode.h"
#include "order.h"

#include "cJSON.h"
#include "cdh_fun_stm32.h"
#include "data_helper.h"
#endif
