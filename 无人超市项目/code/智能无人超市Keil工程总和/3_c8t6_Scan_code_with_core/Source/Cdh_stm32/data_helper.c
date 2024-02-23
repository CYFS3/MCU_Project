#include "data_helper.h"
/*字符串转整型*/
int str_to_int(const char *str)
{
    return (int)strtol(str, NULL, 0);
}
/*字符串转单浮点型*/
float str_to_float(const char *str)
{
    return (float)strtof(str, NULL);
}
/*整型转字符串*/
void int_to_str(int num,char *str)
{
    snprintf(str, sizeof(str),"%d", num);
}
/*单浮点型转字符串*/
void float_to_str(float num, char *str) 
{
    snprintf(str, sizeof(str), "%f", num);
}
