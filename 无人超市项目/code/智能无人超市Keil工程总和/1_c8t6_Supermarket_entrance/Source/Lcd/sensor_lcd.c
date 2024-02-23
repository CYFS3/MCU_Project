#include "sensor_lcd.h"

/*初始化LCD文字*/
void init_lcd_word(void)
{
	LCD_Init();
	LCD_Fill(0,0,LCD_W,LCD_H,HUISE);
}

/*获取第一行的颜色*/
u16 GetColorA(int i)
{
	u16 color_list[4]={GREEN,ORANGE,SKYBLUE,LIGHTCOLOR};
	if(i>3)i=0+i-(4*(i/4));
	return color_list[i];
}
/*获取第二行的颜色*/
u16 GetColorB(int j)
{
	u16 color_list[6]={RED,ORANGE,GREEN,BLUE,LIGHTCOLOR,SKYBLUE};
	if(j>5)j=0+j-(6*(j/6));
	return color_list[j];
}
int color_ii=0;//欢迎来到
int color_jj=32767;//智能无人超市
/*显示“欢迎来到”*/
void LCD_Join_word(void)
{
	LCD_ShowChinese(56+0*32,0+72,(u8*)"A1",GetColorA(color_ii),HUISE,32,0);//data
	LCD_ShowChinese(56+1*32,0+72,(u8*)"A2",GetColorA(color_ii+1),HUISE,32,0);//data
	LCD_ShowChinese(56+2*32,0+72,(u8*)"A3",GetColorA(color_ii+2),HUISE,32,0);//data
	LCD_ShowChinese(56+3*32,0+72,(u8*)"A4",GetColorA(color_ii+3),HUISE,32,0);//data
	color_ii=color_ii>32767 ? 0:color_ii+1;
}
/*显示“智能无人超市”*/
void LCD_cs_word(void)
{
	LCD_ShowChinese(24+0*32,48+72,(u8*)"B1B2",GetColorB(color_jj),HUISE,32,0);//data
	LCD_ShowChinese(24+2*32,48+72,(u8*)"B3B4",GetColorB(color_jj+1),HUISE,32,0);//data
	LCD_ShowChinese(24+4*32,48+72,(u8*)"B5B6",GetColorB(color_jj+2),HUISE,32,0);//data
	color_jj=color_jj<1 ? 32767:color_jj-1;
}
/*更新LCD屏幕(进入超市的LCD)*/
void UpdateWord(void)
{
	LCD_Join_word();
	LCD_cs_word();
	LCD_ShowChinese(24+4*32,48+72,(u8*)"B5B6",GetColorB(color_jj+2),HUISE,32,0);//data
	//LCD_DrawLine(24,48+72+32+3,24+6*32,48+72+32+3,WHITE);
}
