#include "cdh_fun_stm32.h"

/*设置GPIO输出电平*/
void GPIO_Set_Bit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin,u8 state)
{
	if(state)
	{
		GPIO_SetBits(GPIOx,GPIO_Pin);
	}else
	{
		GPIO_ResetBits(GPIOx,GPIO_Pin);
	}
}

