#include "pir.h"

#define pir_PORT GPIOB
#define pir_PIN GPIO_Pin_4
#define pir_RCC RCC_APB2Periph_GPIOB

#define pir_STATE() GPIO_ReadInputDataBit(pir_PORT,pir_PIN)

void pir_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
    
  RCC_APB2PeriphClockCmd(pir_RCC,ENABLE);	
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin =pir_PIN ;
	GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;
	GPIO_Init(pir_PORT ,&GPIO_InitStructure);
}
bool get_pir(void)
{
	return pir_STATE();
}

