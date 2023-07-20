#include "pid.h"
#include "tim.h"
#include "main.h"
#include "math.h"
#include "i2c.h"
#include "oled.h"

unsigned int MotorSpeed1;		//ȫ�ֱ����������ǰת��
int SpeedTarget1 = 30;				//Ŀ��ת��

unsigned int MotorSpeed2;		//ȫ�ֱ����������ǰת��
int SpeedTarget2 = 30;				//Ŀ��ת��


int Error_Last1,Error_Prev1;		//�ϴ������ϴ����
int Pwm_add1,Pwm1 = 0 ;							//PWM����,PWMռ�ձ�
float Kp1 = 1, Ki1 = 1.35, Kd1 = 0;//PID�㷨ϵ�����������ͣ�оƬ��������һ��ʱ�������ͣ�����*1024

int Error_Last2,Error_Prev2;		//�ϴ������ϴ����
int Pwm_add2,Pwm2 = 0 ;							//PWM����,PWMռ�ձ�
float Kp2 = 2, Ki2 = 1.555, Kd2 = 0;//PID�㷨ϵ�����������ͣ�оƬ��������һ��ʱ�������ͣ�����*1024


//TIM2������ת��
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

//����ʽPID

int SpeedInnerControl1(int Speed1,int Target1)		//�ٶ��ڻ�����
{
  int Error1 = Target1 - Speed1;		//��� = Ŀ���ٶ� - ʵ���ٶ�
  Pwm_add1 = Kp1 * (Error1 - Error_Last1) + 										//����
             Ki1 * Error1 +																		//����
             Kd1 * (Error1 - 2.0f * Error_Last1 + Error_Prev1);	//΢��
  Pwm1 += Pwm_add1;		//�����=ԭʼ��+����
  Error_Prev1 = Error_Last1;	//�������ϴ����
  Error_Last1 = Error1;				//�����ϴ����
  if(Pwm1 > 3000)//���Ϊ4999
    Pwm1 = 400;	//���������ޣ���ֹPWM��������zz
  if(Pwm1 < 0)
    Pwm1 = 0;	//���������ޣ���ֹPWM��������zz
  OLED_ShowNum(40,2,Pwm1,4,16);
  return Pwm1;	//�������ֵ

}






//TIM4������ת��

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


//����ʽPID


int SpeedInnerControl2(int Speed2,int Target2)		//�ٶ��ڻ�����
{
  int Error2 = Target2 - Speed2;		//��� = Ŀ���ٶ� - ʵ���ٶ�
  Pwm_add2 = Kp2 * (Error2 - Error_Last2) + 										//����
             Ki2 * Error2 +																		//����
             Kd2 * (Error2 - 2.0f * Error_Last2 + Error_Prev2);	//΢��
  Pwm2 += Pwm_add2;		//�����=ԭʼ��+����
  Error_Prev2 = Error_Last2;	//�������ϴ����
  Error_Last2 = Error2;				//�����ϴ����
  if(Pwm2 > 3000)
    Pwm2 = 400;	//���������ޣ���ֹPWM��������zz
  if(Pwm2 < 0)
    Pwm2 = 0;	//���������ޣ���ֹPWM��������zz
  OLED_ShowNum(40,6,Pwm2,4,16);
  return Pwm2;	//�������ֵ

}


