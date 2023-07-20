#ifndef __MOTOR_H_
#define __MOTOR_H_

#include "stm32f1xx_hal.h"
#include "main.h"

extern TIM_HandleTypeDef htim3;

void MOTOR_GO(void);
void MOTOR_BACK(void);
void MOTOR_STOP(void);
void MOTOR_MLEFT(void);
void MOTOR_MRIGHT(void);
void MOTOR_TLEFT(void);
void MOTOR_TRIGHT(void);
void MOTOR_LEFT_UP(void);
void MOTOR_LEFT_DOWN(void);
void MOTOR_RIGHT_UP();
void MOTOR_RIGHT_DOWN();

#endif
