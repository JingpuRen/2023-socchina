void setup() {
  Car_Init();
  //  HC_SR04_Init();
  Arm_Init();
  //  PS2_Init();
  Serial.write("stop");
  delay(200);
  Arm_Servo6(85);
}

void loop() {
  Car_Follow();
  Arm_Select();
}
