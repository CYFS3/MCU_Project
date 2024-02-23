#include "lcd_init.h"
#include "config.h"

void LCD_GPIO_Init(void)
{

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 |GPIO_Pin_7;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	SPI_InitTypeDef SPI_InitStructure;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI1, &SPI_InitStructure);
	SPI_Cmd(SPI1, ENABLE);
    GPIO_SetBits(GPIOB,GPIO_Pin_6 | GPIO_Pin_7);
    GPIO_SetBits(GPIOA,GPIO_Pin_8);
    
}


/******************************************************************************
      函数说明：LCD串行数据写入函数
      入口数据：dat  要写入的串行数据
      返回值：  无
******************************************************************************/
void LCD_Writ_Bus(u8 dat)
{
	
	
    // Wait until the transmit buffer is empty
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    // Send the byte
    SPI_I2S_SendData(SPI1, dat);
    // Wait until the transmission is complete
    //while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
}


/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void LCD_WR_DATA8(u8 dat)
{
    LCD_Writ_Bus(dat);
}


/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void LCD_WR_DATA(u16 dat)
{
    LCD_Writ_Bus(dat>>8);
    LCD_Writ_Bus(dat);
}


/******************************************************************************
      函数说明：LCD写入命令
      入口数据：dat 写入的命令
      返回值：  无
******************************************************************************/
void LCD_WR_REG(u8 dat)
{
    LCD_DC_Clr();//写命令
    LCD_Writ_Bus(dat);
    LCD_DC_Set();//写数据
}


/******************************************************************************
      函数说明：设置起始和结束地址
      入口数据：x1,x2 设置列的起始和结束地址
                y1,y2 设置行的起始和结束地址
      返回值：  无
******************************************************************************/
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2)
{
    if(USE_HORIZONTAL==0)
    {
        LCD_WR_REG(0x2a);//列地址设置
        LCD_WR_DATA(x1);
        LCD_WR_DATA(x2);
        LCD_WR_REG(0x2b);//行地址设置
        LCD_WR_DATA(y1);
        LCD_WR_DATA(y2);
        LCD_WR_REG(0x2c);//储存器写
    }
    else if(USE_HORIZONTAL==1)
    {
        LCD_WR_REG(0x2a);//列地址设置
        LCD_WR_DATA(x1);
        LCD_WR_DATA(x2);
        LCD_WR_REG(0x2b);//行地址设置
        LCD_WR_DATA(y1+80);
        LCD_WR_DATA(y2+80);
        LCD_WR_REG(0x2c);//储存器写
    }
    else if(USE_HORIZONTAL==2)
    {
        LCD_WR_REG(0x2a);//列地址设置
        LCD_WR_DATA(x1);
        LCD_WR_DATA(x2);
        LCD_WR_REG(0x2b);//行地址设置
        LCD_WR_DATA(y1);
        LCD_WR_DATA(y2);
        LCD_WR_REG(0x2c);//储存器写
    }
    else
    {
        LCD_WR_REG(0x2a);//列地址设置
        LCD_WR_DATA(x1+80);
        LCD_WR_DATA(x2+80);
        LCD_WR_REG(0x2b);//行地址设置
        LCD_WR_DATA(y1);
        LCD_WR_DATA(y2);
        LCD_WR_REG(0x2c);//储存器写
    }
}

void LCD_Init(void)
{
    LCD_GPIO_Init();//初始化GPIO

    LCD_RES_Clr();//复位
    delay_Ms(100);
    LCD_RES_Set();
    delay_Ms(100);

    LCD_BLK_Set();//打开背光
    delay_Ms(100);

    //************* Start Initial Sequence **********//
    LCD_WR_REG(0x11); //Sleep out
    delay_Ms(120);              //Delay 120ms
    //************* Start Initial Sequence **********//
    LCD_WR_REG(0x36);
    if(USE_HORIZONTAL==0)LCD_WR_DATA8(0x00);
    else if(USE_HORIZONTAL==1)LCD_WR_DATA8(0xC0);
    else if(USE_HORIZONTAL==2)LCD_WR_DATA8(0x70);
    else LCD_WR_DATA8(0xA0);

    LCD_WR_REG(0x3A);
    LCD_WR_DATA8(0x05);

    LCD_WR_REG(0xB2);
    LCD_WR_DATA8(0x1F);
    LCD_WR_DATA8(0x1F);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x33);
    LCD_WR_DATA8(0x33);

    LCD_WR_REG(0xB7);
    LCD_WR_DATA8(0x35);

    LCD_WR_REG(0xBB);
    LCD_WR_DATA8(0x20);   //2b

    LCD_WR_REG(0xC0);
    LCD_WR_DATA8(0x2C);

    LCD_WR_REG(0xC2);
    LCD_WR_DATA8(0x01);

    LCD_WR_REG(0xC3);
    LCD_WR_DATA8(0x01);

    LCD_WR_REG(0xC4);
    LCD_WR_DATA8(0x18);   //VDV, 0x20:0v

    LCD_WR_REG(0xC6);
    LCD_WR_DATA8(0x13);   //0x13:60Hz

    LCD_WR_REG(0xD0);
    LCD_WR_DATA8(0xA4);
    LCD_WR_DATA8(0xA1);

    LCD_WR_REG(0xD6);
    LCD_WR_DATA8(0xA1);   //sleep in后，gate输出为GND

    LCD_WR_REG(0xE0);
    LCD_WR_DATA8(0xF0);
    LCD_WR_DATA8(0x04);
    LCD_WR_DATA8(0x07);
    LCD_WR_DATA8(0x04);
    LCD_WR_DATA8(0x04);
    LCD_WR_DATA8(0x04);
    LCD_WR_DATA8(0x25);
    LCD_WR_DATA8(0x33);
    LCD_WR_DATA8(0x3C);
    LCD_WR_DATA8(0x36);
    LCD_WR_DATA8(0x14);
    LCD_WR_DATA8(0x12);
    LCD_WR_DATA8(0x29);
    LCD_WR_DATA8(0x30);

    LCD_WR_REG(0xE1);
    LCD_WR_DATA8(0xF0);
    LCD_WR_DATA8(0x02);
    LCD_WR_DATA8(0x04);
    LCD_WR_DATA8(0x05);
    LCD_WR_DATA8(0x05);
    LCD_WR_DATA8(0x21);
    LCD_WR_DATA8(0x25);
    LCD_WR_DATA8(0x32);
    LCD_WR_DATA8(0x3B);
    LCD_WR_DATA8(0x38);
    LCD_WR_DATA8(0x12);
    LCD_WR_DATA8(0x14);
    LCD_WR_DATA8(0x27);
    LCD_WR_DATA8(0x31);

    LCD_WR_REG(0xE4);
    LCD_WR_DATA8(0x1D);   //使用240根gate  (N+1)*8
    LCD_WR_DATA8(0x00);   //设定gate起点位置
    LCD_WR_DATA8(0x00);   //当gate没有用完时，bit4(TMG)设为0

    LCD_WR_REG(0x21);

    LCD_WR_REG(0x29);
    
    
    LCD_Fill(0,0,LCD_W,LCD_H,BLACK);
	/*温度*/
	LCD_ShowChinese(0,0,(u8*)"QQRRAACC",YELLOW,BLACK,32,0);
	LCD_ShowChar(4*32,0,':',YELLOW,BLACK,32,0);
	LCD_ShowIntNum(5*32-8,0,0,2,BLUE,BLACK,32);//data
	LCD_ShowChinese(6*32,0,(u8*)"SS",YELLOW,BLACK,32,0);
	
	/*湿度*/
	LCD_ShowChinese(0,32,(u8*)"QQRRBBCC",YELLOW,BLACK,32,0);
	LCD_ShowChar(4*32,32,':',YELLOW,BLACK,32,0);
	LCD_ShowIntNum(5*32-8,32,0,2,BLUE,BLACK,32);//data
	LCD_ShowChar(6*32+8,32,'%',YELLOW,BLACK,32,0);
	
	/*光强*/
	LCD_ShowChinese(0,32*2,(u8*)"QQRRFFGG",YELLOW,BLACK,32,0);
	LCD_ShowChar(4*32,32*2,':',YELLOW,BLACK,32,0);
	LCD_ShowIntNum(5*32-10,32*2,0,3,BLUE,BLACK,24);//data
	LCD_ShowString(6*32,32*2,(u8*)"Lux",YELLOW,BLACK,24,0);
	
	/*烟雾浓度*/
	LCD_ShowChinese(0,32*3,(u8*)"QQRRDDEE",YELLOW,BLACK,32,0);
	LCD_ShowChar(4*32,32*3,':',YELLOW,BLACK,32,0);
	LCD_ShowIntNum(5*32-10,32*3,(int)0,3,BLUE,BLACK,24);//data
	LCD_ShowString(6*32,32*3,(u8*)"ppm",YELLOW,BLACK,24,0);
	
	/*有无火焰*/
	LCD_ShowChinese(0,32*4,(u8*)"KKJJHHII",YELLOW,BLACK,32,0);
	LCD_ShowChar(4*32,32*4,':',YELLOW,BLACK,24,0);
	LCD_ShowChinese(5*32,32*4,(u8*)"JJ",WHITE,BLACK,32,0);//data
	
	/*火灾预警*/
	LCD_ShowChinese(0,32*5+16,(u8*)"HHNNOOPP",LIGHT_CYAN,BLACK,32,0);
	LCD_ShowChar(4*32,32*5+16,':',LIGHT_CYAN,BLACK,24,0);
	LCD_ShowChinese(5*32,32*5+16,(u8*)"TTUU",GREEN,BLACK,32,0);//data
    
}







