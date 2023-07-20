#include "motor.h"

extern int Pwm1;
extern int Pwm2;

void MOTOR_GO()
{
  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1,Pwm1);	//PWM调速
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);

  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4,Pwm2);	//PWM调速
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_SET);
}

void MOTOR_BACK()
{
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1,Pwm1);	//PWM调速
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);

  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4,Pwm2);	//PWM调速
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
}

void MOTOR_MLEFT()
{
  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1,Pwm1);	//PWM调速
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);

  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4,Pwm2);	//PWM调速
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_SET);

}

void MOTOR_MRIGHT()
{
  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1,Pwm1);	//PWM调速
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);

  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4,Pwm2);	//PWM调速
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);

}

void MOTOR_TLEFT()
{
  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1,Pwm1);	//PWM调速
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);

  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4,Pwm2);	//PWM调速
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
}

void MOTOR_TRIGHT()
{
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1,Pwm1);	//PWM调速
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);

  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4,Pwm2);	//PWM调速
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_SET);
}

void MOTOR_STOP()
{
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
}

void MOTOR_LEFT_UP()
{
  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1,Pwm1);	//PWM调速
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);

  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4,Pwm2);	//PWM调速
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_SET);
}

void MOTOR_LEFT_DOWN()
{
  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1,Pwm1);	//PWM调速
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);

  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4,Pwm2);	//PWM调速
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
}

void MOTOR_RIGHT_UP()
{
  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1,Pwm1);	//PWM调速
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);

  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4,Pwm2);	//PWM调速
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
}

void MOTOR_RIGHT_DOWN()
{
  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1,Pwm1);	//PWM调速
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);

  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4,Pwm2);	//PWM调速
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
}

