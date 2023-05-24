#include <IRremote.h>
#include <Servo.h>


Servo servo;

int RECV_PIN = A0; // 입력값 핀 설정
IRrecv irrecv(RECV_PIN);
decode_results results;
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // 수신 시작
  servo.attach(7);
}
void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
   
   switch (results.value) {
    
        case '+':
        servo.write(60);
        delay(100);
        servo.write(90);
        break; //1버튼이 눌리면 LED OFF

        case 0xFFE01F:
        servo.write(120);
        delay(100);
        servo.write(90);
        break;
      }
    irrecv.resume(); // 다음 출력값 수신 준비
  }
}
