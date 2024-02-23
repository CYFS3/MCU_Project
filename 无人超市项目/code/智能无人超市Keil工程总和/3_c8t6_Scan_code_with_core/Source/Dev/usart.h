#ifndef _USART_H_
#define _USART_H_
#include "config.h"
extern u16 usart1_pos;//最后一个字符位置
void usart_init_12345(u32 USART1_BaudRate,u32 USART2_BaudRate,u32 USART3_BaudRate,u32 UART4_BaudRate,u32 UART5_BaudRate);

void init_usart1(u32 USART1_BaudRate);
void init_usart2(u32 USART2_BaudRate);
void init_usart3(u32 USART3_BaudRate);
void init_uart4(u32 UART4_BaudRate);
void init_uart5(u32 UART5_BaudRate);
void usart_send_byte(USART_TypeDef* USARTx,u8 ch);
void usart_send_string(USART_TypeDef* USARTx,u8 str[]);


unsigned char USART1_RecProcess(void);
unsigned char USART2_RecProcess(void);
unsigned char USART3_RecProcess(void);
unsigned char UART4_RecProcess(void);

unsigned char UART5_RecProcess(void);
#endif
