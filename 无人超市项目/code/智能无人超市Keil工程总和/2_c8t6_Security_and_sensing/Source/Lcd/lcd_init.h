#ifndef __LCD_INIT_H
#define __LCD_INIT_H

typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned  int u32;
#define USE_HORIZONTAL 3  //设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏


#define LCD_W 240
#define LCD_H 240



//-----------------LCD端口定义---------------- 

#define LCD_SCLK_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_12)//SCL=SCLK PB12
#define LCD_SCLK_Set() GPIO_SetBits(GPIOB,GPIO_Pin_12)

#define LCD_MOSI_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_13)//SDA=MOSI  PB13
#define LCD_MOSI_Set() GPIO_SetBits(GPIOB,GPIO_Pin_13)

#define LCD_RES_Clr()  GPIO_ResetBits(GPIOB,GPIO_Pin_14)//RES  PB14
#define LCD_RES_Set()  GPIO_SetBits(GPIOB,GPIO_Pin_14)

#define LCD_DC_Clr()   GPIO_ResetBits(GPIOB,GPIO_Pin_15)//DC PB15
#define LCD_DC_Set()   GPIO_SetBits(GPIOB,GPIO_Pin_15)

#define LCD_BLK_Clr()  GPIO_ResetBits(GPIOA,GPIO_Pin_8)//BLK PA8
#define LCD_BLK_Set()  GPIO_SetBits(GPIOB,GPIO_Pin_8)




void LCD_GPIO_Init(void);//初始化GPIO
void LCD_Writ_Bus(u8 dat);//模拟SPI时序
void LCD_WR_DATA8(u8 dat);//写入一个字节
void LCD_WR_DATA(u16 dat);//写入两个字节
void LCD_WR_REG(u8 dat);//写入一个指令
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2);//设置坐标函数
void LCD_Init(void);//LCD初始化
#endif




