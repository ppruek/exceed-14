#include <Servo.h> 
Servo myservo;  

#define trig1 10
#define echo1 11
#define trig2 12
#define echo2 13
int duration1,duration2,duration3,duration4;
short people =0;

void setup() {
  Serial.begin(9600);
  myservo.attach(9);
  myservo.write(0);

}

void loop() {  
  pinMode(trig1,OUTPUT);
  delayMicroseconds(2);
  digitalWrite(trig1,HIGH);
  delayMicroseconds(5);
  digitalWrite(trig1,LOW);
  pinMode(echo1, INPUT);
  duration1 = pulseIn(echo1,HIGH);
  delay(500);
  pinMode(trig2,OUTPUT);
  delayMicroseconds(2);
  digitalWrite(trig2,HIGH);
  delayMicroseconds(5);
  digitalWrite(trig2,LOW);
  pinMode(echo2, INPUT);
  duration2 = pulseIn(echo2,HIGH);
  delay(500);
  pinMode(trig1,OUTPUT);
  delayMicroseconds(2);
  digitalWrite(trig1,HIGH);
  delayMicroseconds(5);
  digitalWrite(trig1,LOW);
  pinMode(echo1, INPUT);
  duration3 = pulseIn(echo1,HIGH);
  delay(500);
  pinMode(trig2,OUTPUT);
  delayMicroseconds(2);
  digitalWrite(trig2,HIGH);
  delayMicroseconds(5);
  digitalWrite(trig2,LOW);
  pinMode(echo2, INPUT);
  duration4 = pulseIn(echo2,HIGH);
  delay(500);
  if(duration1 != duration3 && (duration1-duration3 > 100)){
    myservo.write(90); 
    delay(500);
    myservo.write(0);  
    people++;
    }
  else if(duration2 != duration4 && (duration2-duration4 > 100)) {
    myservo.write(90); 
    delay(50);
    myservo.write(0); 
    people--;
    }
  //Serial.println(people);
}

