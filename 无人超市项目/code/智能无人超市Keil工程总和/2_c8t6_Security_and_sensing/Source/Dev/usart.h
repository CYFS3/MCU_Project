#ifndef _USART_H_
#define _USART_H_
#include "config.h"
void usart_init_123(u32 USART1_BaudRate,u32 USART2_BaudRate,u32 USART3_BaudRate);
void init_usart1(u32 USART1_BaudRate);
void init_usart2(u32 USART2_BaudRate);
void init_usart3(u32 USART3_BaudRate);
	
void usart_send_byte(USART_TypeDef* USARTx,u8 ch);
void usart_send_string(USART_TypeDef* USARTx,u8 str[]);
unsigned char USART1_RecProcess(void);
unsigned char USART2_RecProcess(void);
unsigned char USART3_RecProcess(void);
#endif
