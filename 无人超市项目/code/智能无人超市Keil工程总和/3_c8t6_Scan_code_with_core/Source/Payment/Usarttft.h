#ifndef _USARTTFT_H__
#define _USARTTFT_H__
#include "config.h"
#define END "\xff\xff\xff"
typedef struct
{
	Goods goods;
	int number;
	float total_price;
}Single_Goods;

typedef struct{
	int UserID;
	Single_Goods GoodList[100];
	int scanNum;
	float add_price;//累计金额
	float discount;//折扣
	float pay_price;//应付
}Indent;
//void Receive_usarttft(void);
//void Send_usarttft(int order);
void send_indent(const Indent *indent);
void DisposeUsartTTFT(u8 *str);
void setReturnOpenmv(u8 *return_data);
#endif
