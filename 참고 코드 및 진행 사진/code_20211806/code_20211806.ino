#include <Servo.h>
#include <IRremote.h>
#include <LiquidCrystal.h>

#define C 262
#define D 294
#define E 330
#define G 392
#define A 440

int trig = 7;
int echo = 6;
int LED = 5;
int spk = 4;
int RECV_PIN = 3;

Servo servo;
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

IRrecv irrecv(RECV_PIN);
decode_results results;

int alarm[] = {
  G, G, A, A, G, G, E, 0, 
  G, G, E, E, D, 0, 
  G, G, A, A, G, G, E, 0, 
  G, E, D, E, C
}; //학교종 멜로디

int alarmlen = sizeof(alarm) / sizeof(int);

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  lcd.begin(16, 2);
  servo.attach(2);
  irrecv.enableIRIn();
}

void alert() {
  int dis;
  while (1) {
    lcd.write("Wake up!");
    for (int i = 0; i < alarmlen; i++)
    {

      tone(spk, alarm[i], 500);
      delay(500);

      digitalWrite(trig, HIGH);
      delay(1);
      digitalWrite(trig, LOW);
      dis = pulseIn(echo, HIGH) * 340 / 2 / 10000;

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
      lcd.clear();
      lcd.write("Have a Good Day!");
      break;
    }
  }
  return;
}


void loop() {
  digitalWrite(LED, LOW);

  if (irrecv.decode(&results)) {
    //스위치 제어 버튼 중 하나를 누르면
    if (results.value == 0xFFA857 || results.value == 0xFFE01F) {
      lcd.clear();
      lcd.write("LIGHT ");

      switch (results.value) {

        case 0xFFA857: //+버튼

          digitalWrite(LED, HIGH);
          servo.write(110);
          delay(200);
          servo.write(90);
          lcd.write("ON!");

          break; 

        case 0xFFE01F: //-버튼
          digitalWrite(LED, HIGH);
          servo.write(70);
          delay(200);
          servo.write(90);
          lcd.write("OFF!");

          break;
      }
      irrecv.resume();
    }
    
    String Timer = "";
    String Time = "";

    if (results.value == 0xFF906F ) {
      digitalWrite(LED, HIGH);
      delay(100);

      while (1) {
        digitalWrite(LED, LOW);
        if (irrecv.decode(&results)) {
          if (results.value != 0xFFC23D) {
            digitalWrite(LED, HIGH);
            delay(100);

            switch (results.value) //값 지정
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

              case 0xFF629D: //알람 리셋 버튼 (ch)
                Time = "";
                Timer = "";
                lcd.clear();
                lcd.print("Alarm Reset!");
                delay(2000);
                break;
            }
            Timer = Timer + Time;
            lcd.clear();
            lcd.write("ALARM SET");
            lcd.setCursor(0, 1);
            lcd.print(Timer);
          }

          if (results.value == 0xFFC23D)
          {
            digitalWrite(LED, HIGH);
            delay(100);
            digitalWrite(LED, LOW);

            lcd.clear();
            lcd.write("Complete!");

            int data = 0;
            data = Timer.toInt();


            for (int i = 0; i < data; i++) {
              int Clock = data - i;
              lcd.clear();
              lcd.write("Alarm...");
              lcd.setCursor(0, 1);
              lcd.print(Clock);
              lcd.setCursor(String(Clock).length() + 1, 1);
              lcd.write("minute left");

              delay(60000); //1분
            }
            lcd.clear();

            digitalWrite(LED, HIGH); //불 자동으로 키기
            servo.write(110);
            delay(100);
            servo.write(90);

            alert();
            return 0;
          }
          irrecv.resume();
        }
      }
    }
    irrecv.resume();
    irrecv.enableIRIn();
  }
}
