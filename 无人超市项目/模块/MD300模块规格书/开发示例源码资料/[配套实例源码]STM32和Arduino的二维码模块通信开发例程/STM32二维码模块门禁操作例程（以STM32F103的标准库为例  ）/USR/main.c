/******************************************************************
* 功能说明：本程序采用STM32F103ZET6开发板为例，模拟一个简易二维码扫码开锁系统，
采用单片机串口2（PA2,PA3）和模块连接，假定开锁密码为123456，当模块识别到二维码
的字符内容为“123456”并发给单片机解析成功后，单片机就发出一个高电平开锁信号给
PB5引脚，并通过串口1（PA9,PA10）的打印函数输出“开锁成功”的信息，否则输出“开锁失败”
的信息。
此外，本实例还实现了二维码扫描模块的“恢复出厂设置初始化”，解析二维码串口命令
和接收到的字符进行解析匹配的关键功能。
请注意：本代码仅用于工程项目的参考和示范，我们对直接拷贝代码所造成的后果不承担
其他连带责任。 
 * 文件：main.c
 * 功能：主函数入口
 * 日期：2018-02-16
 * 版本：Ver.1.0 | 最初版本
 
* 使用说明:1、编译并下载本例程到任意STM32F103ZET6开发板（如正点原子的战舰开发板）。
*          2、按如下接线（连接二维码模块前4根线，灰紫蓝绿分别对应的是5V,GND,RXD,TXD，不可接错！）：
*          +--------------------+              +--------------------+   
*接串口调试助手RX--|TX1(PA9)    |              |                    |
*          |                 5V |--------------| 5V                 |
*          |  STM32F103ZET   TX2（PA2） |----------| RXD  二维码    |
*          |                 RX2（PA3） |----------| TXD 扫描模块   |
*          |                 GND|--------------| GND                |
*接串口调试助手TX--|RX1(PA10)   |              |                    |
*          +--------------------+              +--------------------+
*          3、打开 “工具 -> 串口监视器”。
*          4、用手机APP生成一个内容为 “666888” 的 QR 二维码,并扫描。
*          5、观察 “串口监视器” 的扫码结果。
*******************************************************************/
#include "stdio.h"
#include "string.h"
#include "DELAY/Delay.h"
#include "LED/LED.h"
#include "KEY/Key.h"
#include "NVIC/NVIC.h"
#include "UART/uart.h"
#include "NetWork.h"

extern u8 TXBuffer[TXBUFFER_LEN];
extern u8 RXBuffer[RXBUFFER_LEN];

int main(void)
{
	

	/*初始化各外设*/ 
    initSysTick();   //精确延时需要用到实时时钟
    initUART();      //初始化串口1,PA9--TX,PA10--RX          
    initUART2();     //初始化串口2,PA2--TX,PA3--RX 
	  initLED();       //初始化开锁功能,PB5
    initNVIC(NVIC_PriorityGroup_2);//开启UART2的接收和空闲中断
    
	 
		if(init_qr_module()!=0)
		{
			Delay_ms(100);
			printf("QR Module now is ready.\r\n");//串口1打印出二维码模块初始化成功的信息
		}
		else
		{
			printf("Initializing QR Module failed,check connections.\r\n");//串口1打印出二维码模块初始化失败的信息，通常是连接问题造成
		}
		
		memset(RXBuffer,0,RXBUFFER_LEN);
		
  
    while (1)
    {	
				
		}
}		
			
			

