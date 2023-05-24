#include <IRremote.h>
#include <Servo.h>

Servo servo; // servo라는 객체 선언

int RECV_PIN = A0; // 입력값 핀 설정
IRrecv irrecv(RECV_PIN);
decode_results results;
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // 수신 시작
  pinMode(12, OUTPUT);//LED 핀 설정
  servo.attach(7); //서보모터 핀 설정
}
void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
   
   switch (results.value) {
        case 0xFF6897:  // 0 버튼
        digitalWrite(12, HIGH); 
        servo.write(90); // 모터 각도 90도
        break; //0버튼이 눌리면 LED ON
        
        case 0xFF30CF:  // 1 버튼
        digitalWrite(12, LOW);
        servo.write(45); // 모터 각도 45도
        break; 
      }
    irrecv.resume(); // 다음 출력값 수신 준비
  }
}
