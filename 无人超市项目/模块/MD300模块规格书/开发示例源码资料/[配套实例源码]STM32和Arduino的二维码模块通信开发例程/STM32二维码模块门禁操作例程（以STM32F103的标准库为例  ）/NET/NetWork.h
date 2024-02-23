/******************************************************************
 * 文件：NetWork.c
 * 功能：声明通信相关函数
 * 日期：2018-04-06
 * 作者：zx
 * 版本：Ver.1.0 | 最初版本
 * 
 * Copyright (C) 2018 zx. All rights reserved.
*******************************************************************/
#ifndef __NETWORK_H
#define __NETWORK_H

#include "stm32f10x.h"
#include "UART/uart.h"



/*发送接收缓冲区长度宏定义*/
#define TXBUFFER_LEN 50
#define RXBUFFER_LEN 50



int init_qr_module(void);
void processServerBuffer(void);


#endif
