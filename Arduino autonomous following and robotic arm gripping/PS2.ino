#include <PS2X_lib.h>
PS2X ps2x;

void PS2_Init() {
  Serial.begin(115200);
  delay(200);
  ps2x.config_gamepad(A3, A1, A2, A0, true, false);
}

void PS2_Car() {
  ps2x.read_gamepad(false, 0);
  delay(30);
  if (ps2x.ButtonPressed(PSB_START)) {
    Serial.write("stop");
  }
  else if (ps2x.ButtonPressed(PSB_PAD_UP)) {
    Serial.write("go");
  }
  else if (ps2x.ButtonPressed(PSB_PAD_DOWN)) {
    Serial.write("back");
  }
  else if (ps2x.ButtonPressed(PSB_PAD_LEFT)) {
    Serial.write("mleft");
  }
  else if (ps2x.ButtonPressed(PSB_PAD_RIGHT)) {
    Serial.write("mright");
  }
  else if (ps2x.ButtonPressed(PSB_L1)) {
    Serial.write("leftup");
  }
  else if (ps2x.ButtonPressed(PSB_R1)) {
    Serial.write("rightup");
  }
  else if (ps2x.ButtonPressed(PSB_L2)) {
    Serial.write("leftdown");
  }
  else if (ps2x.ButtonPressed(PSB_R2)) {
    Serial.write("rightdown");
  }
  else if (ps2x.ButtonPressed(PSB_PINK)) {
    Serial.write("tleft");
  }
  else if (ps2x.ButtonPressed(PSB_RED)) {
    Serial.write("tright");
  }
  else if (ps2x.ButtonPressed(PSB_GREEN) || ps2x.ButtonPressed(PSB_BLUE)) {
    Serial.write("stop");
  }
  else if (ps2x.NewButtonState(PSB_PAD_UP) || ps2x.NewButtonState(PSB_PAD_DOWN) || ps2x.NewButtonState(PSB_PAD_LEFT) || ps2x.NewButtonState(PSB_PAD_RIGHT)
           || ps2x.NewButtonState(PSB_L1) || ps2x.NewButtonState(PSB_L2) || ps2x.NewButtonState(PSB_R1) || ps2x.NewButtonState(PSB_R2)
           || ps2x.NewButtonState(PSB_PINK) || ps2x.NewButtonState(PSB_RED))
  {
    Serial.write("stop");
  }
}

void PS2_Arm() {
  ps2x.read_gamepad(false, 0);
  delay(30);
  if (ps2x.ButtonPressed(PSB_START)) {
    Arm_Init();
  }
  else if (ps2x.ButtonPressed(PSB_GREEN)) {
    Get_Two();
    delay(1500);
    Down_Two();
  }
  else if (ps2x.ButtonPressed(PSB_BLUE)) {
    Get_Four();
    delay(1500);
    Down_Four();
  }
  else if (ps2x.ButtonPressed(PSB_PINK)) {
    Get_One();
    delay(1500);
    Down_One();
  }
  else if (ps2x.ButtonPressed(PSB_RED)) {
    Get_Three();
    delay(1500);
    Down_Three();
  }
}
