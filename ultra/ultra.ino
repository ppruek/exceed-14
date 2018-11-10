#include<Servo.h>
#include<Wire.h>
#include<UnoWiFiDevEd.h>
#define SERVO 3
#define SWITCH 10
#define trig1 10
#define echo1 11 
#define trig2 12
#define echo2 13
#define CONNECTOR "rest"
#define SERVER_ADDR "158.108.165.223"
int people = 0;
String tmpwrite = "";
String tmpread = "";

CiaoData data;

Servo myServo;
boolean isOpen;
int switchinput;

void setup()
{
  Ciao.begin();
  Serial.begin(9600);
  myServo.attach(SERVO);
  pinMode(trig1,OUTPUT);
  pinMode(echo1,INPUT);
  pinMode(trig2,OUTPUT);
  pinMode(echo2,INPUT);
  myServo.write(130);
}

long check1()
{
  long duration, dis1, dis2;
  digitalWrite(trig1, LOW);
  delayMicroseconds(2);
  digitalWrite(trig1, HIGH);
  delayMicroseconds(10);
   digitalWrite(trig1, LOW);
  duration = pulseIn(echo1, HIGH);
  dis1 = (duration/2.0/29.1);
  Serial.print("1: ");
  Serial.println(dis1);
  delay(500);
  return dis1;
}

long check2()
{
  long duration, dis1, dis2;
  digitalWrite(trig2, LOW);
  delayMicroseconds(2);
  digitalWrite(trig2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2 ,LOW);
  duration = pulseIn(echo2, HIGH);
  dis2 = (duration/2.0/29.1);
  Serial.print("2: ");
  Serial.println(dis2);
  delay(500);
  return dis2;
}

void loop()
{
  if(check1()  < 30)
  {
    Serial.print("1: ");
    Serial.println(check1());
    myServo.write(30);
    while(1)
    {
      Serial.print("a1: ");
      Serial.print(check1());
      Serial.print("inwhile: ");
      delay(500);
      if(check2() < 30)
      {
        Serial.print("b2: ");
        Serial.print(check2());
        myServo.write(120);
        people++;
        Serial.print("people: ");
        Serial.print(people);
        Serial.print("out: ");
        break;
      }
    }
    delay(1000);
  }
  else if (check2() < 30)
  {
    Serial.print("2: ");
    Serial.print(check2());
    myServo.write(30);
    while(1)
    {
      Serial.print("inwhile: ");
      if(check1() < 30)
      {
        Serial.print("1: ");
        Serial.print(check1());
        myServo.write(120);
        people--;
        Serial.print("people: ");
        Serial.print(people);
        Serial.print("out: ");
        break;
      }
    }
    delay(500);
  }
}
