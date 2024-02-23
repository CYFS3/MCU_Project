#ifndef _SCANCODE_H__
#define _SCANCODE_H__
#include "config.h"


int Scan_Goods(void);
void setScanCode(char *scan_code);
char* getScanCode(void);
void setCodePage(bool isDispose);
bool getCodePage(void);
void CalculateIndent(void);
void UpdateIndent(void);
void Startbill(int user_id);
void change_discount(float nowdiscount);

#endif
