#include "smoke_MQ.h"

/*获取烟雾浓度 PA1*/
float GetSmokescope(void)
{
    float adc_value/*adc转化值*/,smoke_v/*adc转化后电压*/,smokescope/*ppm值*/;
    adc_value=Get_Adc1_Average(MQ_CHANNEL,5);//获取adc转化值
    smoke_v=adc_value*(3.3/4096.0);//计算引脚电压，单位V
    float RS=0,R0=0,Ratio;
    RS=(3.3/smoke_v-1)*10000; // 修改电源电压为3.3V，与ADC参考电压保持一致
    R0=13700;
    Ratio=RS/R0;
    smokescope=10.0f*pow((Ratio),-2.0f); // 使用括号明确优先级
    return smokescope;
}
