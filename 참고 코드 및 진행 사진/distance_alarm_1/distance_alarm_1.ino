#include "pitches.h" //음계별 주파수 저장됨

#define C 262 //도를 뜻하는 주파수 262를 C로 정의

int trig=7;
int echo=6;
const int spk=9;

void setup(){
  Serial.begin(9600);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
}
void loop(){
 //스피커를 통해 C값인 292 즉, 도의 음을 내라
  digitalWrite(trig,HIGH);
  delay(1);
  digitalWrite(trig,LOW);
  int dis=pulseIn(echo,HIGH)*340/2/10000;
  // 초음파 발생 시간을 계산해 거리(cm)단위로 표현
  Serial.print(dis);
  Serial.println("cm");
  if (dis<40){ //40cm 이내에 물체가 있으면 알람 멈춤
   noTone(spk);
   exit(0);
  }
  delay(100);
}
