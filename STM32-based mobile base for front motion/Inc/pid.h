#ifndef __PID_H
#define __PID_H

//全局变量
extern unsigned int MotorSpeed1;
extern int SpeedTarget1;
extern int MotorOutput1;

extern unsigned int MotorSpeed2;
extern int SpeedTarget2;
extern int MotorOutput2;

//函数申明
//void GetMotorPulse(void);
int SpeedInnerControl1(int Speed,int Target);
int SpeedInnerControl2(int Speed,int Target);

int GetMotorSpeed1(void);
int GetMotorSpeed2(void);
//void SetMotorVoltageAndDirection(int Pwm);
void ModePID1(void);
void ModePID2(void);
#endif
