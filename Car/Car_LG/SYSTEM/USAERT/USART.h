#ifndef __USART_H__
#define __USART_H__
#include "config.h"

#define USART1_RXBUF_SIZE 256
#define USART1_BAUD 115200


void USARTInit(void);
void USARTSendByte(USART_TypeDef* USARTx,u8 ch);
void USARTSendString(USART_TypeDef* USARTx,u8 *str);
unsigned char USART1_RecProsess(void);
void init_usart2(u32 USART2_BaudRate);
#endif


