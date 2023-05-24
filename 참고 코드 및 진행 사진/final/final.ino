#include <Servo.h>
#include <IRremote.h>
#include "pitches.h"

Servo servo;

#define C 262
#define D 294
#define E 330
#define F 349
#define G 392
#define A 440
#define B 494

int trig = 7;
int echo = 6;
int LED = 5;
int spk =4;
int RECV_PIN =3;


IRrecv irrecv(RECV_PIN);
decode_results results;

int alarm[] = {
 G,G,A,A,G,G,E,0,G,G,E,E,D,0,G,G,A,A,G,G,E,0,G,E,D,E,C
};
int alarmlen = sizeof(alarm) / sizeof(int);

void setup() {
  Serial.begin(9600);

  pinMode(LED, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  servo.attach(7);
  irrecv.enableIRIn();
}

void alert() {
  int dis;
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

void loop() {
  digitalWrite(LED, LOW);

  if (irrecv.decode(&results)) {
    irrecv.resume();
    Serial.print("입력 : ");
    Serial.println(results.value, HEX);
    if (results.value == 0xFFA857 || results.value == 0xFFE01F) {

      switch (results.value) {

        case 0xFFA857:
          digitalWrite(LED, HIGH);
          servo.write(110);
          delay(200);
          servo.write(90);
          break; //1버튼이 눌리면 LED OFF

        case 0xFFE01F:
          digitalWrite(LED, HIGH);
          servo.write(70);
          delay(200);
          servo.write(90);
          break;
      }
      irrecv.resume();
    }

    String Timer = "";
    String Time = "";

    if (results.value == 0xFF906F ) {
      digitalWrite(LED, HIGH);
      Serial.println( " go to alarm setting ");
      delay(100);
      irrecv.resume();
      //여기까진 성공, 이후 값에따른 숫자 할당하면 됨

      while (1) {
        digitalWrite(LED, LOW);

        if (irrecv.decode(&results)) {
          irrecv.resume();
          Serial.println("set number");
          delay(300);//연속된 입력을 피하기 위해

          if (results.value != 0xFFC23D) {
            digitalWrite(LED, HIGH);
            delay(100);

            switch (results.value)
            {
              case 0xFF6897:
                Time = "0";
                break;

              case 0xFF30CF:
                Time = "1";
                break;

              case 0xFF18E7:
                Time = "2";
                break;

              case 0xFF7A85:
                Time = "3";
                break;

              case 0xFF10EF:
                Time = "4";
                break;

              case 0xFF38C7:
                Time = "5";
                break;

              case 0xFF5AA5:
                Time = "6";
                break;

              case 0xFF42BD:
                Time = "7";
                break;

              case 0xFF4AB5:
                Time = "8";
                break;

              case 0xFF52AD:
                Time = "9";
                break;
            }
            Timer = Timer + Time;
            Serial.println(Timer);
          }

          if (results.value == 0xFFC23D)
          {
            digitalWrite(LED, HIGH);
            delay(100);
            digitalWrite(LED, LOW);

            Serial.println("Alarm Setting Done!");
            int data = 0;
            data = Timer.toInt();
            Serial.print(data);
            Serial.println("minute!");
            delay(data);//1을 입력하면 *60000 1분으로 계산->분단위변환

            digitalWrite(LED, HIGH); //불 자동으로 키기
            servo.write(110);
            delay(100);
            servo.write(90);

            alert();
            break;
          }
        }
      }
    }
  }
}
