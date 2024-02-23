#ifndef __HANSHU_H__
#define __HANSHU_H__

#include "config.h"
typedef struct
{
    char RC_OK;
    char RC_Timer;
} RC_state;
extern RC_state rc_state;
void LED1_OFF(void);
void LED1_ON(void);
void water_OFF(void);
void water_ON(void);
void DHT11_show(void);
void RC522_read_card(void);
void Door_open(void);
void Door_close(void);
void DH11_OLED_Init(void);



#endif

