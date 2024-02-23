#include "Goods.h"
#include "config.h"

Goods goods[GOODSNUMMAX];//储存商品
unsigned int Goodsnum=0;//商品种类



void Goods_Init(void)
{
	
	W25QXX_Read((u8*)&Goodsnum,1024*1024*4-4,4);
	if(Goodsnum<'\xff')
	for(int i=0;i<Goodsnum;i++)
	{
		W25QXX_Read((u8*)(goods+i),1024*1024+i*64,64);
	}else{
		Goodsnum=0;
	}
	
	
}

void Add_Goods(void)
{
	Goodsnum++;
}

void Save_Goods_falsh(void)
{
	goods[0].Num=1;
	goods[0].Price=2;
	sprintf((char*)(goods[0].BarCodeID),"%s","6917878000879");
	sprintf(goods[0].Name,"%s","脆脆鲨");
	goods[1].Num=2;
	goods[1].Price=15;
	sprintf((char*)(goods[1].BarCodeID),"%s","6954432710225");
	sprintf(goods[1].Name,"%s","炫迈口香糖");
	goods[2].Num=3;
	goods[2].Price=3;
	sprintf((char*)(goods[2].BarCodeID),"%s","6922255447833");
	sprintf(goods[2].Name,"%s","百岁山");
	goods[3].Num=4;
	goods[3].Price=4;
	sprintf((char*)(goods[3].BarCodeID),"%s","6975682480058");
	sprintf(goods[3].Name,"%s","果粒橙");
	goods[4].Num=5;
	goods[4].Price=4;
	sprintf((char*)(goods[4].BarCodeID),"%s","6925303730574");
	sprintf(goods[4].Name,"%s","阿萨姆原味奶茶");
	goods[5].Num=6;
	goods[5].Price=4;
	sprintf((char*)(goods[5].BarCodeID),"%s","6925303789183");
	sprintf(goods[5].Name,"%s","阿萨姆茉莉奶茶");
	goods[6].Num=7;
	goods[6].Price=5;
	sprintf((char*)(goods[6].BarCodeID),"%s","6902083922658");
	sprintf(goods[6].Name,"%s","AD钙奶");
	goods[7].Num=8;
	goods[7].Price=4;
	sprintf((char*)(goods[7].BarCodeID),"%s","6926892515030");
	sprintf(goods[7].Name,"%s","花生牛奶");
	Goodsnum=8;
//	W25QXX_Write((u8*)&Goodsnum,1024*1024*4-4,4);
//	for(int i=0;i<Goodsnum;i++)
//	{
//		W25QXX_Write((u8*)(goods+i),1024*1024+i*64,64);
//	}
}



