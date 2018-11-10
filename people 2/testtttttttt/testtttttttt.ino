#include<Wire.h>
#include<UnoWiFiDevEd.h>
#define CONNECTOR "rest"
#define SERVER_ADDR "158.108.165.223"
String writeAddr;
CiaoData data;
//------------------------------------
#include <Servo.h>
Servo myServo;

#define trig1 10
#define echo1 11
#define trig2 12
#define echo2 13
int duration1, duration2;
short people = 0;
short door = 0;
//-------------------------------------
#include <dht.h>
#define DHT11 2
#define AIR 3
#define LED 7
#define LDR A0 

short value = 0; 

dht DHT;
int dhtTemp;
int temperature;
short air,light;
//-------------------------------------
String all = "";

void setup() {
  Ciao.begin();
  Serial.begin(9600);
  myServo.attach(9);
  myServo.write(0);
  pinMode(LED,OUTPUT);
  pinMode(AIR,OUTPUT);
}

void loop() {
  loop_people();
  loop_temp();
  all = (String)light +"-"+ (String)air +"-"+ (String)door +"-"+ (String)people +"-"+ (String)temperature +"-"+ (String)value;
  writeAddr = "/data/CEEDney/set/all"; 
  data = Ciao.write(CONNECTOR, SERVER_ADDR, writeAddr);
  if (!data.isEmpty()) {
    Ciao.println("State: " + String(data.get(1)));
    Ciao.println("Response: " + String(data.get(2)));
    Serial.println(F("succeed"));
  }
  else {
    Serial.println(F("Write Error")); //use less memory
  }
  delay(1000);
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

void loop_people()
{
  if(check1()  < 23)
  {
    Serial.print("1: ");
    Serial.println(check1());
    myServo.write(0);
    while(1)
    {
      Serial.print("a1: ");
      Serial.print(check1());
      Serial.print("inwhile: ");
      delay(500);
      if(check2() < 20)
      {
        Serial.print("b2: ");
        Serial.print(check2());
        myServo.write(90);
        people++;
        Serial.print("people: ");
        Serial.print(people);
        Serial.print("out: ");
        break;
      }
    }
    delay(1000);
  }
  else if (check2() < 20)
  {
    Serial.print("2: ");
    Serial.print(check2());
    myServo.write(0);
    while(1)
    {
      Serial.print("inwhile: ");
      if(check1() < 20)
      {
        Serial.print("1: ");
        Serial.print(check1());
        myServo.write(90);
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
void loop_temp() {
  dhtTemp =DHT.read11(DHT11);
 temperature =(int) DHT.temperature;
 Serial.print("temperature = ");
 Serial.println(temperature);
 if( temperature > 25 && temperature<31)
 {
  analogWrite(AIR, 25 + 20*(temperature-25)/5 );
  air = 1;
 }
 else if ( temperature <=25)
 {
  analogWrite(AIR, 0);
  air = 0;
 }
 delay(2000);
  
value = analogRead(LDR); 
Serial.print("Light Intensity : ");
Serial.println(value); 
if(value >600)
{
  digitalWrite(LED,HIGH);
  light = 1;
}
 else if (value <600)
 {
  digitalWrite(LED,LOW);
  light = 0;
 }
delay(2000);
}

