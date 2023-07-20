#ifndef __MOTOR_H_
#define __MOTOR_H_

#include "stm32f1xx_hal.h" 
#include "main.h"

extern TIM_HandleTypeDef htim3;

void MOTOR_GO(void); 
void MOTOR_BACK(void);
void MOTOR_STOP(void);     
void MOTOR_UP(void);
void MOTOR_DOWN(void); 

#endif
