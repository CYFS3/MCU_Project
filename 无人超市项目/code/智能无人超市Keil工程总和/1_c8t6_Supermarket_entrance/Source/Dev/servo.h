#ifndef __SERVO_H__
#define __SERVO_H__

#include "config.h"
void Servo_Init(void);
void Servo_angle(float angle);
void open_door(void);
void close_door(void);
bool isDoor_(void);
#endif
