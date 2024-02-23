#ifndef _COMMAND_H_
#define _COMMAND_H_
#include "config.h"
#define USART_PC USART1
#define USART_entrance USART2
#define USART_SensorSafe USART3
#define USART_ScanCode UART4
#define USART_Wifi UART5
void SendMessageTo_PC(char *message);
void SendCommandTo_entrance(bool is_EIC,bool is_door);
void SendCommandTo_Security_and_sensing(bool is_EIC,bool is_lamp,bool is_beep,bool is_fan);
void SendCommandTo_ScanCode(bool is_EIC,bool is_door,float discount);
void SendCommandTo_ScanCode_Add_Goods(u32 ID,const char *GoodsBarCode,const char *GoodsName,float price);
#endif
