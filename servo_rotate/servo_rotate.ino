#include<Servo.h>
Servo myservo;

void setup()
{
  Serial.begin(9600);
  myservo.attach(9);
  myservo.write(120); //then change to 180       120
}

void loop() {
  // put your main code here, to run repeatedly:

}
