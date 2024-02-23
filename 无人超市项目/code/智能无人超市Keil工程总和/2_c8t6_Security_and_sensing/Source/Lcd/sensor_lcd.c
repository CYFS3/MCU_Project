#include "sensor_lcd.h"

/*初始化LCD文字*/
void init_lcd_word(void)
{
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
	data.SmokeScope=102;
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

/*更新传感器数值到lcd屏幕*/
void change_show_lcd(void)
{
	/*温度*/
	LCD_ShowIntNum(5*32-8,0,data.temp,2,data.temp<=28?SKYBLUE:ORANGE,BLACK,32);//data
	
	/*湿度*/
	LCD_ShowIntNum(5*32-8,32,data.humi,2,HUMICOLOR,BLACK,32);//data
	
	/*光强*/
	LCD_ShowIntNum(5*32-10,32*2,data.light,3,LIGHTCOLOR,BLACK,24);//data
	
	/*烟雾浓度*/
	LCD_ShowIntNum(5*32-10,32*3,(int)data.SmokeScope,3,MQ2COLOR,BLACK,24);//data
	
	/*有无火焰*/
	LCD_ShowChinese(5*32,32*4,(u8*)((!data.is_fire)?"JJ":"KK"),(!data.is_fire)?WHITE:RED,BLACK,32,0);//data
	/*火灾预警*/
	LCD_ShowChinese(5*32,32*5+16,(u8*)((!data.is_beep)?"TTUU":"VVWW"),(!data.is_beep)?GREEN:RED,BLACK,32,0);//data
}
