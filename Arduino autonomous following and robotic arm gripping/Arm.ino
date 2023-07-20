#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// 默认地址 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();     //SDA--A4   SCL--A5

volatile int comchar;
char val = ' '; //接收串口发送过来的值

void Arm_Init() {
  Serial.begin(115200);
  pwm.begin();
  pwm.setPWMFreq(50);  // 50HZ更新频率，相当于20ms的周期
}

void Arm_Catch()
{
//   Arm_Servo6(70);
Arm_slow6_HL(85,65);
}

void Arm_Release()
{
//   Arm_Servo6(85);
Arm_slow6_LH(65,85);
}
//void Arm_Init()
//{
////  Arm_Servo6(70);          //爪子闭合角度
//  Arm_Servo1(65);
//  Arm_Servo5(55);
//  Arm_Servo4(15);
//  Arm_Servo3(160);
//  Arm_Servo2(43);
//}
//
void Arm_Select() {
  if (Serial.available() > 0) { //检验在串口缓存区中是否有数据，如果有则返回1，没有就是0.
    val = char(Serial.read());
    delay(10);
  }

  if (val == '1') { //
    Get_One();
    delay(1500);
    Down_One();
  }
  if (val == '2') { //
    Get_Two();
    delay(1500);
    Down_Two();
  }
  if (val == '3') { //
    Get_Three();
    delay(1500);
    Down_Three();
  }
  if (val == '4') { //
    Get_Four();
    delay(1500);
    Down_Four();
  }
  if (val == '5'){
    Serial.write("go");
    val = 0;
    delay(10);
  }
  else if (val == '6'){
    Serial.write("back");
    val = 0;
    delay(10);
  }
  else if (val == '7'){
    Serial.write("tleft");
    val = 0;
    delay(10);
  }
  else if (val == '8'){
    Serial.write("tright");
    val = 0;
    delay(10);
  }
  else if(val == '9'){
    Serial.write("stop");
    val = 0;
  }
}
//------------------------------------------------------------------------------//
//------------------------------------------------------------------------------//
void Arm_Servo1(int pos) {
  pos = map(pos, 0, 180, 102, 510);
  pwm.setPWM(0, 0, pos);
}

void Arm_Servo2(int pos) {
  pos = map(pos, 0, 180, 102, 510);
  pwm.setPWM(1, 0, pos);
}

void Arm_Servo3(int pos) {
  pos = map(pos, 0, 180, 102, 510);
  pwm.setPWM(2, 0, pos);
}

void Arm_Servo4(int pos) {
  pos = map(pos, 0, 180, 102, 510);
  pwm.setPWM(3, 0, pos);
}

void Arm_Servo5(int pos) {
  pos = map(pos, 0, 180, 102, 510);
  pwm.setPWM(4, 0, pos);
}

void Arm_Servo6(int pos) {
  pos = map(pos, 0, 180, 102, 510);
  pwm.setPWM(5, 0, pos);
}
//------------------------------------------------------------------------------//
//------------------------------------------------------------------------------//
void Arm_slow1_LH(int posL, int posH) {
  for (posL; posL < posH; posL++) {
    Arm_Servo1(posL);
    delay(20);
  }
}

void Arm_slow1_HL(int posH, int posL) {
  for (posH; posH > posL; posH--) {
    Arm_Servo1(posH);
    delay(20);
  }
}

void Arm_slow2_LH(int posL, int posH) {
  for (posL; posL < posH; posL++) {
    Arm_Servo2(posL);
    delay(20);
  }
}

void Arm_slow2_HL(int posH, int posL) {
  for (posH; posH > posL; posH--) {
    Arm_Servo2(posH);
    delay(20);
  }
}

void Arm_slow3_LH(int posL, int posH) {
  for (posL; posL < posH; posL++) {
    Arm_Servo3(posL);
    delay(20);
  }
}

void Arm_slow3_HL(int posH, int posL) {
  for (posH; posH > posL; posH--) {
    Arm_Servo3(posH);
    delay(20);
  }
}

void Arm_slow4_LH(int posL, int posH) {
  for (posL; posL < posH; posL++) {
    Arm_Servo4(posL);
    delay(20);
  }
}

void Arm_slow4_HL(int posH, int posL) {
  for (posH; posH > posL; posH--) {
    Arm_Servo4(posH);
    delay(20);
  }
}

void Arm_slow5_LH(int posL, int posH) {
  for (posL; posL < posH; posL++) {
    Arm_Servo5(posL);
    delay(20);
  }
}

void Arm_slow5_HL(int posH, int posL) {
  for (posH; posH > posL; posH--) {
    Arm_Servo5(posH);
    delay(20);
  }
}

void Arm_slow6_LH(int posL, int posH) {
  for (posL; posL < posH; posL++) {
    Arm_Servo6(posL);
    delay(20);
  }
}

void Arm_slow6_HL(int posH, int posL) {
  for (posH; posH > posL; posH--) {
    Arm_Servo6(posH);
    delay(20);
  }
}
//------------------------------------------------------------------------------//
//------------------------------------------------------------------------------//
