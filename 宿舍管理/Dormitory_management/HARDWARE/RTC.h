#ifndef __RTC_H__
#define __RTC_H__
#include "config.h"
typedef struct
{
	vu16 year;
	vu8 month;
	vu8 date;
	vu8 hour;
	vu8 minute;
	vu8 second;
    char * week;
    
}RTC_Calendar;

extern RTC_Calendar calendar ;

void RTC_Init(void);
void RTC_Get(void);
void RTC_Set(u16 year,u8 mon,u8 date,u8 hour,u8 min,u8 Sec);
char * RTC_Get_Week(u32 t1);
void RTC_Alarm_Set(u16 year,u8 mon,u8 date,u8 hour,u8 min,u8 Sec);


#endif

