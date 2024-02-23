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

/* System */
#include "system.h"
#include "systick.h"
#include "task.h"

/* DEV库 */
#include "usart.h"
#include "usart_receive.h"

/* 用户库 */
#include "Encoder.h"
#include "Car_TB6612.h"
#include "Grayscale.h"
#include "Pid.h"
#include "Track.h"

#endif
