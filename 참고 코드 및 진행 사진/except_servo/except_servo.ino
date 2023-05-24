#include <Servo.h>
#include <IRremote.h>
#include "pitches.h"

Servo servo;

#define C 262
#define D 294
#define E 330

int spk = 9;
int trig = 2;
int echo = 3;
int dis;

int RECV_PIN = A0; // 입력값 핀 설정
IRrecv irrecv(RECV_PIN);
decode_results results;

int alarm[] = {
  E, D, C, D, E, E, E, E, D,
  D, D, D, E, E, E, E,
  E, D, C, D, E, E, E, E,
  D, D, E, D, C, C, C
};
int alarmlen = sizeof(alarm) / sizeof(int);

void setup() {
  Serial.begin(9600);

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  servo.attach(7);
  irrecv.enableIRIn();
}

void loop() {

  if (Serial.available()) {
    String ser = Serial.readString();
    Serial.println(ser);
    int angle;
    angle = ser.toInt();
    servo.write(angle);
    if (ser == "alarm" ) {
      Serial.println( " go to alarm setting ");
      String Timer = "0";
      while (1) {
        if (Serial.available()) {
          String Time = Serial.readString();
          Serial.println(Time);
          Timer = Timer + Time;
          Serial.println(Timer);

          if (Time == "s" ) {
            Serial.println( " Timer Start! ");
            break;
          }
        }
      }
      int data;
      data = Timer.toInt();
      delay(data); //1을 입력하면 1분으로 계산->분단위변환
      while (1) {

        for (int i = 0; i < alarmlen; i++)
        {
          tone(spk, alarm[i], 500);
          delay(500);

          digitalWrite(trig, HIGH);
          delay(1);
          digitalWrite(trig, LOW);
          dis = pulseIn(echo, HIGH) * 340 / 2 / 10000;
          Serial.print(dis);
          Serial.println("cm");
          if (dis < 50) {
            noTone(spk);
            break;
          }

        }
        if (dis > 50) {
          noTone(spk);
          delay(700);
        }
        else {
          Serial.println("It's time to wake up!");
          break;
        }
      }
    }
  }
}
