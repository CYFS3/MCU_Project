#ifndef _GOODS_H__
#define _GOODS_H__    
#include "stm32f10x.h"                  // Device header

#define GOODSNAMEMAX 36 //商品名称最大长度
#define GOODSNUMMAX 50//商品的最大数目
#define BARCODEMAX 20
typedef struct {
	unsigned int Num;//商品编号
	unsigned char BarCodeID[BARCODEMAX];//商品条形码
	char Name[GOODSNAMEMAX];//商品名称
	float Price;//商品价格
}Goods;

extern Goods goods[GOODSNUMMAX];
extern unsigned int Goodsnum;

void Goods_Init(void);
void Add_Goods(void);
void Save_Goods_falsh(void);

#endif
