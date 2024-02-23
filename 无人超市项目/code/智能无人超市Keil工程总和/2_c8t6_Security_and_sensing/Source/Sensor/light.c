#include "light.h"

/*获取光照值 PA0*/
u32 GetLightLux(void)
{
	float adc_value,light_mv;
	u16 light_lux;
	adc_value=Get_Adc1_Average(LIGHT_CHANNEL,5);
	
	light_mv=adc_value*3300.0/4096.0;
	light_lux=(u16)(((3300-light_mv)/2.0/10.0)*(3300-light_mv)/1000.0);
	return light_lux;
}
