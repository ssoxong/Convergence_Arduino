#include "pitches.h"

#define C 262

int trig=2;
int echo=3;
const int spk=9;

void setup(){
  Serial.begin(9600);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
}
void loop(){
  tone(spk,C);
  digitalWrite(trig,HIGH);
  delay(1);
  digitalWrite(trig,LOW);
  int dis=pulseIn(echo,HIGH)*340/2/10000;
  Serial.print(dis);
  Serial.println("cm");
  if (dis<40){
   noTone(spk);
   exit(0);
  }
  delay(100);
}
