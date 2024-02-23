#include "config.h"
#include "RTC.h"

#define RTC_CLOCK_SOURCE_LSE
void RTC_CLKConfig(void)
{
#ifdef RTC_CLOCK_SOURCE_LSE //如果选用LSE时钟，用下面的语句配置
	RCC_LSEConfig(RCC_LSE_ON);//外界低速晶体振荡器开启
	while(RCC_GetFlagStatus(RCC_FLAG_LSERDY)==RESET){}//等待LSE准备好
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);//配置RTC时钟源为LSE	（根据开发板硬件看具体频率，通常为32.768KHz的外接晶体振荡器）
	RCC_RTCCLKCmd(ENABLE);//开启RTC时钟
	RTC_WaitForSynchro();    //等待RTC寄存器同步 	
	RTC_WaitForLastTask();//等待最近一次对RTC寄存器的写操作完成
		
	RTC_SetPrescaler(32768-1);//设置预分频系数，让计数脉冲一秒一个	
	RTC_WaitForLastTask();//等待最近一次对RTC寄存器的写操作完成		
	RTC_ITConfig(RTC_IT_SEC,ENABLE);//开启秒中断
    RTC_ITConfig(RTC_IT_ALR,ENABLE);
	RTC_WaitForLastTask();//等待最近一次对RTC寄存器的写操作完成		
#else //如果选择LSI时钟，用下面的语句配置
	RCC_LSICmd(ENABLE);//使能内部低速时钟LSI
	while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY)==RESET){}//等待LSI准备好
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);//配置RTC时钟源为LSI	（LSI通常40KHz）
	RCC_RTCCLKCmd(ENABLE);//开启RTC时钟
	RTC_WaitForSynchro();    //等待RTC寄存器同步 	
	RTC_WaitForLastTask();//等待最近一次对RTC寄存器的写操作完成
		
	RTC_SetPrescaler(40000-1);//设置预分频系数，让计数脉冲一秒一个	
	RTC_WaitForLastTask();//等待最近一次对RTC寄存器的写操作完成		
	RTC_ITConfig(RTC_IT_SEC,ENABLE);//开启秒中断
	RTC_WaitForLastTask();//等待最近一次对RTC寄存器的写操作完成		
#endif	


}	

void RTC_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP | RCC_APB1Periph_PWR,ENABLE);
    PWR_BackupAccessCmd(ENABLE);
    RTC_CLKConfig();
    if(BKP_ReadBackupRegister(BKP_DR1)!=0x0001)
    {
        BKP_DeInit();
        RTC_Set(2023,12,4,14,44,01);
        BKP_WriteBackupRegister(BKP_DR1,0x0001);
    }
    else
    {
        RTC_WaitForSynchro();
        RTC_ITConfig(RTC_IT_SEC,ENABLE);//开启秒中断
        RTC_ITConfig(RTC_IT_ALR,ENABLE);
		RTC_WaitForLastTask();
        
    }
    NVIC_InitTypeDef  NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel=RTC_IRQn;//中断通道号到stm32f10x.h里找IRQn
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;//中断使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;	//主优先级，值越小，优先级越高
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;				//次优先级
	NVIC_Init(&NVIC_InitStructure);
	RTC_Get();//让时间结构体在初始化的时候就能读到时间值
    RTC_Alarm_Set(2023,12,4,14,44,02);
}
//RTC秒中断服务函数，函数名要到.s启动文件里找
void RTC_IRQHandler(void){
//判断是否是需要的中断
	if(RTC_GetITStatus(RTC_IT_SEC)==SET){
		//读取RTC计数值，转换成年月日时分秒
		RTC_Get();
		RTC_ClearITPendingBit(RTC_IT_SEC);
		RTC_WaitForLastTask();//等待最近一次对RTC寄存器的写操作完成	
	}
   

}



/**
	* @brief  判断闰年函数
	* @param  u16 year:年份
  * @retval u8 1:闰年;0:平年
  * @note   
  *         
  */
u8 Is_Leap_Year(u16 year){
	if(((year%4==0)&&(year%100!=0))||(year%400==0)){
		return 1;
	}
	else return 0;
}


//读取RTC计数值(秒钟数)，转换成年月日时分秒
//一天：24x60x60=86400秒
//平年 365天x86400秒=31536000秒
//闰年 366天x86400秒=31622400秒
RTC_Calendar calendar={1970,1,1,0,0,0,"四"};
const u8 mon_table[12]={31,28,31,30,31,30,31,31,30,31,30,31};//平年每月的天数
void RTC_Get(void){
static u16 daycnt=0;//天数计数器，用于当天的不同秒中断进来时，不重复计算年月日
	u32 timecount=0;
	u32 temp=0;//用于计算日期时存储天数	
	u16 temp1;//临时变量，用于计算日期时存储年份、月份	
	timecount=RTC_GetCounter();//得到RTC计数值(秒钟数)
		temp=timecount/86400;//整天
		if(daycnt!=temp){
			daycnt=temp;
		temp1=1970;
		//计算年份
		while(temp>=365){
			if(Is_Leap_Year(temp1)==1){//闰年
				if(temp>=366){temp-=366;temp1++;}
				else break;//闰年的最后一天，这一年还没过完，年份不能加
			}
			else{temp-=365;temp1++;}//平年	
		}//退出while循环的时候，temp1里就是年份，temp里时剩下不满1年的天数
			calendar.year=temp1;//得到年份
		//计算月份
		temp1=0;//temp1改做月份计算
		while(temp>=28){
			if((Is_Leap_Year(temp1)==1)&&(temp1==1)){//当年是闰年且计算到2月的时候
				if(temp>=29){temp-=29;temp1++;}
				else break;//闰月的第29天，这个月还没过完，月份不能加
			}
			else{//平年
				if(temp>=mon_table[temp1]){temp-=mon_table[temp1];temp1++;}
				else break;//不满1个月，这个月还没过完，月份不能加
			}	 
		}//退出while循环的时候，temp1里就是已过去的完整的月份数，temp里时剩下不满1个月、且完整过完的天数。
		calendar.month=temp1+1;//得到当月=已过去的完整月份+1
		//计算日期
		calendar.date=temp+1;//得到当日=已过去的完整天数+1
	}	
	//计算时分秒
	temp=timecount%86400;//得到不满1天的秒钟数
	calendar.hour=temp/3600;//得到小时
	calendar.minute=(temp%3600)/60;//得到分钟
	calendar.second=(temp%3600)%60;//秒
    calendar.week = RTC_Get_Week(timecount);
}


/**
	* @brief  把时间写入RTC的函数
	* @param  u16 year:年份，u8 mon月，u8 date日，u8 hour时，u8 min分，u8 Sec 秒
    * @retval None
	* @note   把输入参数年月日时分秒转换成相对于1970.1.1 0:0:0走过的秒钟数，写入到RTC的CNT里。
  *				 	一天：24x60x60=86400秒
  * 				平年 365天x86400秒=31536000秒
  * 				闰年 366天x86400秒=31622400秒 
  */
void RTC_Set(u16 year,u8 mon,u8 date,u8 hour,u8 min,u8 Sec){
	u16 t;
	u32 Seccount=0;//秒钟数
	if(year<1970||year>2099)return;
	
	for(t=1970;t<year;t++){//累加已过去的年份对应的秒钟数
		if(Is_Leap_Year(t)==1){//闰年
			Seccount+=31622400;//闰年一年的秒钟数
		}
		else{
			Seccount+=31536000;//平年一年的秒钟数
		}
	}//Seccount里就是已过去的年份对应的秒钟数
	
	mon-=1;//完整过去的月份
	for(t=0;t<mon;t++){
		Seccount+=mon_table[t]*86400;//每个月的秒钟数=该月的天数*1天的秒钟数
   if(Is_Leap_Year(t)==1&&t==1){//闰年且当月mon大于2月份（2月份已过去）
		 Seccount+=86400;
	 }
	}//Seccount里就是已过完的年份和当年已过完的月份对应的秒钟数
	Seccount+=(u32)(date-1)*86400;//已过完的天数对应的秒钟数
	Seccount+=(u32)hour*3600;//小时对应的秒钟数
	Seccount+=(u32)min*60;//分钟对应的秒钟数
	Seccount+=Sec;//秒对应的秒钟数	
	//把秒钟数写入RTC的CNT寄存器
	//1、使能PWR和BKP时钟：RCC_APB1PeriphClockCmd();
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP|RCC_APB1Periph_PWR,ENABLE);
	//2、使能后备寄存器访问: PWR_BackupAccessCmd();
	PWR_BackupAccessCmd(ENABLE);	
	RTC_SetCounter(Seccount);//设置RTC_CNT计数器的值
	RTC_WaitForLastTask();//等待最近一次对RTC寄存器的写操作完成	
}

/**
	* @brief  计算某个日期是星期几
	* @param  RTC读取出来的秒钟数
    * @retval 星期几的字符串
    * @note   以1970.1.1星期四作为参考点
    *		  t1/86400%7，作为星期几的数组下标
  * 				
  */
char * Week[7]={"四","五","六","日","一","二","三"};
char * RTC_Get_Week(u32 t1)
{
    return Week[(t1 / 86400) % 7];
}


void RTC_Alarm_Set(u16 year,u8 mon,u8 date,u8 hour,u8 min,u8 Sec){
	u16 t;
	u32 Seccount=0;//秒钟数
	if(year<1970||year>2099)return;
	
	for(t=1970;t<year;t++){//累加已过去的年份对应的秒钟数
		if(Is_Leap_Year(t)==1){//闰年
			Seccount+=31622400;//闰年一年的秒钟数
		}
		else{
			Seccount+=31536000;//平年一年的秒钟数
		}
	}//Seccount里就是已过去的年份对应的秒钟数
	
	mon-=1;//完整过去的月份
	for(t=0;t<mon;t++){
		Seccount+=mon_table[t]*86400;//每个月的秒钟数=该月的天数*1天的秒钟数
   if(Is_Leap_Year(t)==1&&t==1){//闰年且当月mon大于2月份（2月份已过去）
		 Seccount+=86400;
	 }
	}//Seccount里就是已过完的年份和当年已过完的月份对应的秒钟数
	Seccount+=(u32)(date-1)*86400;//已过完的天数对应的秒钟数
	Seccount+=(u32)hour*3600;//小时对应的秒钟数
	Seccount+=(u32)min*60;//分钟对应的秒钟数
	Seccount+=Sec;//秒对应的秒钟数	
	//把秒钟数写入RTC的CNT寄存器
	//1、使能PWR和BKP时钟：RCC_APB1PeriphClockCmd();
	
	//2、使能后备寄存器访问: PWR_BackupAccessCmd();
	
	RTC_SetAlarm(Seccount);//
}

