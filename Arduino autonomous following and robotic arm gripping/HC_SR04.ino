const int Trig_1 = 2;
const int Echo_1 = 3;

const int Trig_2 = 4;
const int Echo_2 = 5;

const int Trig_3 = 10;
const int Echo_3 = 11;

double distance, Time;

void HC_SR04_Init() {
  Serial.begin(115200);  // 初始化串口通信及连接SR04的引脚
  pinMode(Trig_1, OUTPUT);
  pinMode(Echo_1, INPUT);  //要检测引脚上输入的脉冲宽度，需要先设置为输入状态
  pinMode(Trig_2, OUTPUT);
  pinMode(Echo_2, INPUT);  //要检测引脚上输入的脉冲宽度，需要先设置为输入状态
  pinMode(Trig_3, OUTPUT);
  pinMode(Echo_3, INPUT);  //要检测引脚上输入的脉冲宽度，需要先设置为输入状态
  pinMode(13, OUTPUT);
}
int Get_Distance_1() {
  digitalWrite(Trig_1, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig_1, HIGH);
  delayMicroseconds(10);  //产生一个10us的高脉冲去触发SR04
  digitalWrite(Trig_1, LOW);
  Time = pulseIn(Echo_1, HIGH);  // 检测脉冲宽度，注意返回值是微秒us
  distance = Time / 58;        //计算出距离,输出的距离的单位是厘米cm
  delay(10);
  Serial.print(distance);                                //把得到的距离值通过串口通信返回给电脑，通过串口监视器显示出来
  Serial.println("cm");
  return distance;
}

int Get_Distance_2() {
  digitalWrite(Trig_2, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig_2, HIGH);
  delayMicroseconds(10);  //产生一个10us的高脉冲去触发SR04
  digitalWrite(Trig_2, LOW);
  Time = pulseIn(Echo_2, HIGH);  // 检测脉冲宽度，注意返回值是微秒us
  distance = Time / 58;        //计算出距离,输出的距离的单位是厘米cm
  delay(10);
  Serial.print(distance);                                //把得到的距离值通过串口通信返回给电脑，通过串口监视器显示出来
  Serial.println("cm");
  return distance;
}

int Get_Distance_3() {
  digitalWrite(Trig_3, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig_3, HIGH);
  delayMicroseconds(10);  //产生一个10us的高脉冲去触发SR04
  digitalWrite(Trig_3, LOW);
  Time = pulseIn(Echo_3, HIGH);  // 检测脉冲宽度，注意返回值是微秒us
  distance = Time / 58;        //计算出距离,输出的距离的单位是厘米cm
  delay(10);
  Serial.print(distance);                                //把得到的距离值通过串口通信返回给电脑，通过串口监视器显示出来
  Serial.println("cm");
  return distance;
}
