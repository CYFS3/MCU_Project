#ifndef _DATA_HELPER_H_
#define _DATA_HELPER_H_
#include <stdio.h>
#include <stdlib.h>
int str_to_int(const char *str);
float str_to_float(const char *str);
void int_to_str(int num,char *str,size_t str_size);
void float_to_str(float num, char *str,size_t str_size);
#endif
