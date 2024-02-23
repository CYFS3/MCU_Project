#ifndef _FAN_H_
#define _FAN_H_
#include "config.h"
void init_fan(void);
void SetFanState(bool state);
bool GetFanState(void);
#endif
