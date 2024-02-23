#include "wifi.h"

/*初始化wifi*/
void init_wifi(void)
{
	DelayMs(500);
	usart_send_string(USART_Wifi,(u8*)"AT\r\n");
	DelayMs(2000);
	usart_send_string(USART_Wifi,(u8*)"AT+CIPSTART=\"TCP\",\"192.168.12.71\",9800\r\n");
	DelayMs(2000);
	usart_send_string(USART_Wifi,(u8*)"AT+CIPMODE=1\r\n");
	DelayMs(500);
	usart_send_string(USART_Wifi,(u8*)"AT+CIPSEND\r\n");
	DelayMs(500);
	usart_send_string(USART_PC,(u8*)"初始化wifi成功！\r\n");
}