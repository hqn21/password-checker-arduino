#include <Servo.h>

Servo myServo;

int mada = 9;
int ledA = 11;
int ledB = 6;
int openOption = 2;

int haha = 0;

void setup() {
  myServo.attach(mada);
  pinMode(ledA, OUTPUT);
  pinMode(ledB, OUTPUT);
}

void loop() {
  //if(digitalRead(openOption)) {
  if(haha == 0) {
    digitalWrite(ledA, HIGH);
    digitalWrite(ledB, LOW);
    myServo.write(0);
    haha = 1;
    delay(100);
  }
  else {
    digitalWrite(ledA, LOW);
    digitalWrite(ledB, HIGH);
    myServo.write(180);
    haha = 0;
    delay(100);
  }
}
