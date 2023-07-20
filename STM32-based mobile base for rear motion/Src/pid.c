#include "pid.h"
#include "tim.h"
#include "main.h"
#include "math.h"
#include "i2c.h"
#include "oled.h"

unsigned int MotorSpeed1;		//全局变量，电机当前转速
int SpeedTarget1 = 30;				//目标转速

unsigned int MotorSpeed2;		//全局变量，电机当前转速
int SpeedTarget2 = 30;				//目标转速


int Error_Last1,Error_Prev1;		//上次误差，上上次误差
int Pwm_add1,Pwm1 = 0 ;							//PWM增量,PWM占空比
float Kp1 = 1, Ki1 = 1.35, Kd1 = 0;//PID算法系数，浮点类型，芯片计算能力一般时建议整型，或者*1024

int Error_Last2,Error_Prev2;		//上次误差，上上次误差
int Pwm_add2,Pwm2 = 0 ;							//PWM增量,PWM占空比
float Kp2 = 2, Ki2 = 1.555, Kd2 = 0;//PID算法系数，浮点类型，芯片计算能力一般时建议整型，或者*1024


//TIM2计算电机转速
int GetMotorSpeed1(void)
{
  int CaptureNumber1 =	(short)(__HAL_TIM_GET_COUNTER(&htim2));	  //???????
  __HAL_TIM_SET_COUNTER(&htim2,0);
  MotorSpeed1=CaptureNumber1;
  if (CaptureNumber1 < 0)
    {
      MotorSpeed1 = -MotorSpeed1;
      OLED_ShowNum(40,0,MotorSpeed1,4,16);
    }
  else
    {
      MotorSpeed1 = MotorSpeed1;
      OLED_ShowNum(40,0,MotorSpeed1,4,16);
    }
//	HAL_Delay(25);
////	OLED_CLS();
  return MotorSpeed1;
}

void ModePID1()
{
  GetMotorSpeed1();
  if (MotorSpeed1 != 0)
    {
      SpeedInnerControl1(MotorSpeed1,SpeedTarget1);
    }
				  if (MotorSpeed1 == 0)
    {
      Pwm1 = 10;
			SpeedInnerControl1(MotorSpeed1,SpeedTarget1);
    }
		

}

//增量式PID

int SpeedInnerControl1(int Speed1,int Target1)		//速度内环控制
{
  int Error1 = Target1 - Speed1;		//误差 = 目标速度 - 实际速度
  Pwm_add1 = Kp1 * (Error1 - Error_Last1) + 										//比例
             Ki1 * Error1 +																		//积分
             Kd1 * (Error1 - 2.0f * Error_Last1 + Error_Prev1);	//微分
  Pwm1 += Pwm_add1;		//输出量=原始量+增量
  Error_Prev1 = Error_Last1;	//保存上上次误差
  Error_Last1 = Error1;				//保存上次误差
  if(Pwm1 > 3000)//最大为4999
    Pwm1 = 400;	//限制上下限，防止PWM超出量程zz
  if(Pwm1 < 0)
    Pwm1 = 0;	//限制上下限，防止PWM超出量程zz
  OLED_ShowNum(40,2,Pwm1,4,16);
  return Pwm1;	//返回输出值

}






//TIM4计算电机转速

int GetMotorSpeed2(void)
{
  int  CaptureNumber2 =(short)(__HAL_TIM_GET_COUNTER(&htim4));	  //???????
  __HAL_TIM_SET_COUNTER(&htim4,0);
  MotorSpeed2=CaptureNumber2;
  if (CaptureNumber2 < 0)
    {
      MotorSpeed2= -MotorSpeed2;
      OLED_ShowNum(40,4,MotorSpeed2,4,16);
    }
  else
    {
      MotorSpeed2= MotorSpeed2;
      OLED_ShowNum(40,4,MotorSpeed2,4,16);
    }
//	//	HAL_Delay(25);
////	OLED_CLS();
  return MotorSpeed2;

}

void ModePID2()
{
  GetMotorSpeed2();
  if (MotorSpeed2 != 0)
    {
      SpeedInnerControl2(MotorSpeed2,SpeedTarget2);
    }
				  if (MotorSpeed2 == 0)
    {
      Pwm2 = 10;
			SpeedInnerControl2(MotorSpeed2,SpeedTarget2);
    }

}


//增量式PID


int SpeedInnerControl2(int Speed2,int Target2)		//速度内环控制
{
  int Error2 = Target2 - Speed2;		//误差 = 目标速度 - 实际速度
  Pwm_add2 = Kp2 * (Error2 - Error_Last2) + 										//比例
             Ki2 * Error2 +																		//积分
             Kd2 * (Error2 - 2.0f * Error_Last2 + Error_Prev2);	//微分
  Pwm2 += Pwm_add2;		//输出量=原始量+增量
  Error_Prev2 = Error_Last2;	//保存上上次误差
  Error_Last2 = Error2;				//保存上次误差
  if(Pwm2 > 3000)
    Pwm2 = 400;	//限制上下限，防止PWM超出量程zz
  if(Pwm2 < 0)
    Pwm2 = 0;	//限制上下限，防止PWM超出量程zz
  OLED_ShowNum(40,6,Pwm2,4,16);
  return Pwm2;	//返回输出值

}


