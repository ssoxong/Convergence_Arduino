#include <Servo.h>

Servo servo;
int angle;

void setup(){
  Serial.begin(9600);
  servo.attach(7);
}
void loop(){
  while(Serial.available()>0){
    angle=Serial.parseInt();
    Serial.println(angle);
    if (Serial.read()=='\n'){
      servo.write(angle);
      delay(15);
    }
  }
}
