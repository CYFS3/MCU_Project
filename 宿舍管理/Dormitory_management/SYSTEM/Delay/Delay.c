#include "config.h"
/**
  * @brief  微秒级延时
  * @param  xus 延时时长，范围：0~233015
  * @retval 无
  */
void delay_Us(uint32_t xus)
{
    u32 delta;
    u32 current_delay;
    xus = xus*(SysTick->LOAD/1000);
    delta=SysTick->VAL;
    do
    {
        if(delta > SysTick->VAL)current_delay=delta-SysTick->VAL;
        else current_delay=SysTick->LOAD + delta -	SysTick->VAL;
    }
    while(current_delay < xus);
}

/**
  * @brief  毫秒级延时
  * @param  xms 延时时长，范围：0~4294967295
  * @retval 无
  */
void delay_Ms(uint32_t xms)
{
    while(xms--)
    {
        delay_Us(1000);
    }
}

/**
  * @brief  秒级延时
  * @param  xs 延时时长，范围：0~4294967295
  * @retval 无
  */
void delay_S(uint32_t xs)
{
    while(xs--)
    {
        delay_Ms(1000);
    }
}
