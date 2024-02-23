#include "config.h"

u8 UuID[4],Ttemp[4];
u8 Temp[4],UID[4];
RC_state rc_state = {0,0};
void LED1_OFF(void)
{
    GPIO_ResetBits(GPIOB,GPIO_Pin_0);
}
void LED1_ON(void)
{
    GPIO_SetBits(GPIOB,GPIO_Pin_0);
}

void water_OFF(void)
{
    GPIO_ResetBits(GPIOB,GPIO_Pin_1);
}
void water_ON(void)
{
    GPIO_SetBits(GPIOB,GPIO_Pin_1);
}

void DH11_OLED_Init(void)
{
    OLED_Init();
    OLED_Clear();
    OLED_ShowCH(0,0,(u8*)"T:");
    OLED_ShowCH(60,0,(u8*)"H:");
}
//显示DHT11温湿度到oled函数
void DHT11_show(void)
{


    DHT11_REC_Data();
    //printf("temp:%d,humi:%d\r\n",rec_data[2],rec_data[0]);
    OLED_ShowNum(32,0,rec_data[2],2,1);
    OLED_ShowNum(92,0,rec_data[0],3,1);
}

//RFID识别
void RC522_read_card(void)
{
    if (PcdRequest(0x52, Ttemp) == MI_OK)
    {
        printf("ok\r\n");
        if (PcdAnticoll(UuID) == MI_OK)
        {
            printf("open door\r\n");
            rc_state.RC_OK = 1;

        }
    }
}

void Door_open(void)
{
    TIM_SetCompare1(TIM3,10);
}
void Door_close(void)
{
    TIM_SetCompare1(TIM3,22);
}





