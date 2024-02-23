/******************************************************************
 * 文件：NetWork.c
 * 功能：实现数据通信解析相关函数
 * 日期：2018-04-06
 * 版本：Ver.1.0 | 最初版本
*******************************************************************/
#include "stdio.h"
#include "string.h"
#include "NetWork.h"
#include "LED/LED.h"
#include "RELAY/Relay.h"
#include "DELAY/Delay.h"



u8 TXBuffer[TXBUFFER_LEN] = {0};  //串口通信数据发送缓冲
u8 RXBuffer[RXBUFFER_LEN] = {0};  //串口通信数据接收缓冲
int init_qr_module_flag;

/**
 * 功能：数据通信解析函数，查找字符串中是否包含另一个字符串
 * 参数：
 *       dest：待查找目标字符串
 *       src：待查找内容
 *       retry_cn:查询超时时间
 * 返回值：查找结果，非0为查找成功,0为失败
 * 说明：
 *       当发出一个指令后，需要一段时间等待二维码模块回复,因此就需要等待一段时间,
 *       这个时间通常是几百ms,其实花不了那么多时间,但如果发生超时
 *       就一定可以判断是通信问题
 */
static u8 findStr(u8* dest,u8* src,u16 retry_cn)
{
    u16 retry = retry_cn;                   //超时时间
    u8 result_flag = 0;                     //查找结果

    while(strstr((const char*)dest,(const char*)src)==0 && --retry!=0)//等待串口接收完毕或超时退出
    {
        Delay_ms(10);
    }

   if(retry==0)                            //如果超时则有问题,此时返回0
   {
       return 0;
   }
   result_flag = 1;                        //执行到这里说明一切正常, 表示查找成功

    if(result_flag)
    {
        return 1;
    }else 
    {
        return 0;
    }
}

int init_qr_module(void)
{
	memset(RXBuffer,0,RXBUFFER_LEN); //清空接收缓冲
	memset(TXBuffer,0,RXBUFFER_LEN); //清空发送缓冲
	sendString(USART2,"R_CMD_RESET\r\n");   //复位二维码模块，默认115200波特率,8,n,1，无协议的串口透明传输模式
	Delay_ms(200);

	if(findStr(RXBuffer,"OK",200)!=0)//返回OK，表明二维码模块复位成功
    {
        init_qr_module_flag = 1;//模块初始化成功标志
			  return 1;
    }
	else 
    {
        return 0;
    }
		
}



/**
 * 功能：处理服务器发回来的控制指令
 * 参数：None
 * 返回值：None
 */
void processServerBuffer(void)
{ 
    u8 i = 0;

    /*开锁状态控制*/
	if(init_qr_module_flag == 1) 
  {		
	 if(strstr((const char*)RXBuffer,"123456"))
    {
        ++i;
			  open_door;
			printf("Unlocking successful. The password is 123456.\r\n");
        
    }
		else 
    {
        ++i;
			  close_door;
        printf("Unlocking failed. Wrong password.\r\n");
    }
	}
   
    /*只在接收控制指令时才清空,这样可避免接收命令时导致失败*/
    if(i!=0)
    {
        memset(RXBuffer,0,RXBUFFER_LEN);
    }          
}
