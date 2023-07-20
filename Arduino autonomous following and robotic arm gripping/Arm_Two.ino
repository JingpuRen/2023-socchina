void Get_Two()
{
//  Arm_Servo1(87);
//  Arm_Servo2(85);
//  Arm_Servo3(180);
//  Arm_Servo4(98);
//  Arm_Servo5(80);
//  Arm_Servo6(90);
  Arm_slow2_LH(43, 105);
  Arm_slow3_HL(160, 150);
  Arm_slow4_LH(15, 55);
  Arm_Servo6(90);
  Arm_slow1_LH(65, 87);
  Arm_Servo5(80);
  Arm_slow4_LH(55, 105);
  Arm_slow3_LH(150, 180);
  Arm_slow2_HL(105, 75);
  delay(1000);
  Arm_Catch();
  delay(1000);
}

void Down_Two()
{
  Arm_slow2_LH(75, 105);
  Arm_slow3_HL(180, 150);
  Arm_slow4_HL(105, 55);
  Arm_slow1_HL(87, 65);
  
  Arm_slow4_LH(55, 75);
  Arm_slow5_HL(80, 55);
  Arm_slow2_HL(105, 70);
  Arm_slow3_HL(150, 120);
  Arm_slow2_HL(70, 50);
  Arm_slow3_HL(120, 105);
  Arm_slow2_HL(50, 37);
  delay(1000);
  Arm_Release();
  delay(1000);
  Arm_slow2_LH(37, 50);
  Arm_slow3_LH(105, 120);
  Arm_slow2_LH(50, 80);
  Arm_slow3_LH(120, 160);
  Arm_slow2_LH(80, 105);
  
  Arm_slow4_HL(75, 15);
  Arm_slow2_HL(105, 43);
}
