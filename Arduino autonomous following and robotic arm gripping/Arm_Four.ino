void Get_Four()
{
//  Arm_Servo1(57);
//  Arm_Servo2(65);
//  Arm_Servo3(150);
//  Arm_Servo4(90);
//  Arm_Servo5(45);
//  Arm_Servo6(90);

  Arm_slow2_LH(43, 105);
//  Arm_slow3_HL(160, 150);
  Arm_slow4_LH(15, 55);
//  Arm_Servo6(90);
  Arm_slow1_HL(65, 57);
  Arm_Servo5(45);
  Arm_slow4_LH(55, 95);
  Arm_slow3_HL(160, 150);
  Arm_slow2_HL(105, 60);
  delay(1000);
  Arm_Catch();
  delay(1000);
}

void Down_Four()
{
  Arm_slow2_LH(60, 105);
  Arm_slow3_LH(150, 160);
//  Arm_slow4_HL(95, 55);
  Arm_slow1_LH(57, 65);
  Arm_slow3_HL(160, 140);
  Arm_slow4_HL(95, 75);
  Arm_slow5_LH(45, 55);
  Arm_slow2_HL(105, 70);
  Arm_slow3_HL(140, 120);
  Arm_slow2_HL(70, 37);
  Arm_slow3_HL(120, 105);
  delay(1000);
  Arm_Release();
  delay(1000);
  Arm_slow3_LH(105, 120);
  Arm_slow2_LH(37, 80);
  Arm_slow3_LH(120, 160);
  Arm_slow2_LH(80, 105);
  Arm_slow4_HL(75, 55);

  Arm_slow4_HL(55, 15);
  Arm_slow2_HL(105, 43);
}
