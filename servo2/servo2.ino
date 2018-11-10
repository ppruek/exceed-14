#include <Servo.h>
Servo myservo;
void setup()
{
  Serial.begin(9600);
  myservo.attach(9);
  myservo.write(0);
}
void loop()
{
  Serial.println("sucess");
  myservo.write(110);
  delay(1000);  
  myservo.write(180);
  delay(1000);
}
