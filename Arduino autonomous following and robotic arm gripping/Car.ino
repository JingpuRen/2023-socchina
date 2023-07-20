#include <SoftwareSerial.h>

SoftwareSerial portOne(6, 7); // TX, RX 虚拟软串口
SoftwareSerial portTwo(8, 9); // TX, RX 虚拟软串口
byte comdataL[3] = {}; //接受左边传感器的数据
int DistanceL = 6800; //左边小车的距离发送模块的距离
byte comdataR[3] = {}; //接受右边传感器的数据
int DistanceR = 6800; //右边小车的距离发送模块的距离

static byte index_L = 0, index_R = 0;

void Car_Init() {
  Serial.begin(115200);
  portOne.begin(115200);
  portTwo.begin(115200);
}

void ReadDistances()
{
  ReadDistances_L();
  ReadDistances_R();
}

int ReadDistances_L()
{
  portOne.listen();
  delay(20);          //防止串口卡死
  while (portOne.available())                   //如果串口数据可用
  {
    if (index_L == 0)
    {
      comdataL[index_L] = portOne.read();       //把获取传感器的数据存放到数组里面
      if (comdataL[index_L] == 0xA5)            //判断数据的头文件
        index_L++;
    }
    else
    {
      comdataL[index_L++] = portOne.read();
    }
  }
  if (index_L >= 3)
  {
    index_L = 0;
    DistanceL = comdataL[1] << 8 | comdataL[2];    //把收到的数据合成为距离值
  }
  portOne.end();
  return DistanceL;
}

int ReadDistances_R()
{
  portTwo.listen();
  delay(20);                                       //防止串口卡死
  while (portTwo.available())                      //如果串口数据可用
  {
    if (index_R == 0)
    {
      comdataR[index_R] = portTwo.read();          //把获取传感器的数据存放到数组里面
      if (comdataR[index_R] == 0xA5)               //判断数据的头文件
        index_R++;
    }
    else
    {
      comdataR[index_R++] = portTwo.read();
    }
  }

  if (index_R >= 3)
  {
    index_R = 0;
    DistanceR = comdataR[1] << 8 | comdataR[2];    //把收到的数据合成为距离值
//      Serial.print("L:");
//      Serial.println(DistanceL);
//      Serial.print("R:");
//      Serial.println(DistanceR);
//      Serial.println("------------------------------------------------");
//      delay(100);
  }
  portTwo.end();
  return DistanceR;
}

void Car_Follow()
{
   if((1000 <= ReadDistances_L() && ReadDistances_L() <= 3000) || (1000 <= ReadDistances_R() && ReadDistances_R() <= 3000) 
   || ((ReadDistances_L() > 6000) && (ReadDistances_R() < 6000)) || ((ReadDistances_R() > 6000) && (ReadDistances_L() < 6000)))
   {
      if(-60 <= (DistanceR-DistanceL) && (DistanceR-DistanceL) <= 60)
      {
        Serial.write("go");
        while(-60 <= (ReadDistances_R()-ReadDistances_L()) && (ReadDistances_R()-ReadDistances_L()) <= 60){Arm_Select();}
      }
      if((DistanceR-DistanceL) < -60 || ((ReadDistances_L() > 6000) && (ReadDistances_R() < 6000)))
      {
        Serial.write("tleft");
        while(((ReadDistances_R()-ReadDistances_L()) < -60) || ((ReadDistances_L() > 6000) && (ReadDistances_R() < 6000))){Arm_Select();}
      }
      if((DistanceR-DistanceL) > 60)
      {
        Serial.write("tright");
        while((ReadDistances_R()-ReadDistances_L()) > 60){Arm_Select();}
      }
   }
   if((700 <= ReadDistances_R() && ReadDistances_R() <= 800) && (700 <= ReadDistances_L() && ReadDistances_L() <= 800))
   {
//    Serial.write("back");
//    while((700 < ReadDistances_R() && ReadDistances_R() < 800) && (700 < ReadDistances_L() && ReadDistances_L() < 800)){Arm_Select();}
      if(-60 <= (DistanceR-DistanceL) && (DistanceR-DistanceL) <= 60)
      {
        Serial.write("back");
        while(-60 <= (ReadDistances_R()-ReadDistances_L()) && (ReadDistances_R()-ReadDistances_L()) <= 60);
      }
      if((DistanceR-DistanceL) < -60 || ((ReadDistances_L() > 6000) && (ReadDistances_R() < 6000)))
      {
        Serial.write("tleft");
        while(((ReadDistances_R()-ReadDistances_L()) < -60) || ((ReadDistances_L() > 6000) && (ReadDistances_R() < 6000))){Arm_Select();}
      }
      if((DistanceR-DistanceL) > 60)
      {
        Serial.write("tright");
        while((ReadDistances_R()-ReadDistances_L()) > 60){Arm_Select();}
      }
   }
   if(ReadDistances_R() > 3000 || ReadDistances_L() >3000 || (800 < ReadDistances_R() && ReadDistances_R() < 1000)
   || (800 < ReadDistances_L() && ReadDistances_L() < 1000)|| (ReadDistances_L() < 700 && ReadDistances_L() < 700))
   {
    Serial.write("stop");
    while(ReadDistances_R() > 3000 || ReadDistances_L() >3000 || (800 < ReadDistances_R() && ReadDistances_R() < 1000)
   || (800 < ReadDistances_L() && ReadDistances_L() < 1000)|| (ReadDistances_L() < 700 && ReadDistances_L() < 700)){Arm_Select();}
   }
}
