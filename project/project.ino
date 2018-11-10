#include <Servo.h>
Servo myservo_1;
//----------watering---------
#define gear_water1 2
#define gear_water2 3
bool chk = false;
//----------fan for humidity---------
#include <dht.h>
#define DHT11 4
dht DHT;
short dhtTemp;
short dhtHumid;
short temperature;
short humidity;
//----------temp--------
#define LDR A0
#define LED1 5
short light_intensity;
//----------light-------
//#define trig 10
//#define echo 11
//#define gear1 2
//#define gear2 3
//#define gear3 4
//#define gear4 5
short dis_mushroom;
int duration_mushroom;
short count = 0;
//----------mushroom----
#define trig 12
#define echo 13
short lv_water;
int duration_water;
//----------water-------
char software_press_fan;
char software_press_servo1;
char light_from_software;
char software_press_lang;
////////////////////////
#include<Wire.h>
#include<UnoWiFiDevEd.h>
#define CONNECTOR "rest"
#define SERVER_ADDR "158.108.165.223"
String writeAddr;
CiaoData data;
//------------------------------------

void setup()
{
  Ciao.begin();
  Serial.begin(9400);
  myservo_1.attach(9);
  myservo_1.write(0);
  pinMode(LED1, OUTPUT);
  //pinMode(gear1, OUTPUT);
  //pinMode(gear2, OUTPUT);
  //pinMode(gear3, OUTPUT);
  //pinMode(gear4, OUTPUT);
  pinMode(gear_water1, OUTPUT);
  pinMode(gear_water2, OUTPUT);
  pinMode(trig, OUTPUT);
}

void loop()
{
  dhtTemp = DHT.read11(DHT11);
  dhtHumid = DHT.read11(DHT11);
  temperature = (short) DHT.temperature;
  writeAddr = "/data/CEEDney/set/" + (String)temperature;
  data = Ciao.write(CONNECTOR, SERVER_ADDR, writeAddr);
  humidity = (short) DHT.humidity;
  writeAddr = "/data/CEEDney/set/" + (String)humidity;
  data = Ciao.write(CONNECTOR, SERVER_ADDR, writeAddr);

  if (software_press_fan == 'a') {
    analogWrite(gear_water1, 100);
    analogWrite(gear_water2, 0);
  }
  else if (software_press_fan == 'b') {
    analogWrite(gear_water1, 0);
    analogWrite(gear_water2, 0);
  }
  ///////////////////////////////////////////////////////
  if (software_press_servo1 == 'c') {
    myservo_1.write(180);
  }
  else if (software_press_servo1 == 'd') {
    myservo_1.write(0);
  }
  else if (humidity > 80 ) {
    chk = true;
    while (chk) {
      dhtHumid = DHT.read11(DHT11);
      humidity = (short) DHT.humidity;
      writeAddr = "/data/CEEDney/set/" + (String)humidity;
      data = Ciao.write(CONNECTOR, SERVER_ADDR, writeAddr);
      if (humidity < 80) { //80% of huminity of mushroom
        chk = false;
        break;
      }
      analogWrite(gear_water1, 100);
      analogWrite(gear_water2, 0);
    }
    analogWrite(gear_water1, 0);
    analogWrite(gear_water2, 0);
  }
  ///////////////////////////////////////////////////////
  if (light_from_software == 'g') {
    analogWrite(LED1, 255);
  }
  else if (light_from_software == 'h') {
    light_intensity = analogRead(LDR);
    writeAddr = "/data/CEEDney/set/" + (String)light_intensity;
    data = Ciao.write(CONNECTOR, SERVER_ADDR, writeAddr);
    analogWrite(LED1, 10);
    if (dis_mushroom < 100) { //dis_mushroom find in ultrasonic
      analogWrite(LED1, 200);
    }
    else if (dis_mushroom < 400) {
      analogWrite(LED1, 100);
    }
    else {
      analogWrite(LED1, 10);
    }
  }
  ///////////////////////////////////////////////////////
  /*if (software_press_lang == 'e') {
    analogWrite(gear1, 0);
    analogWrite(gear2, 100);
    analogWrite(gear3, 0);
    analogWrite(gear4, 100);
    delay(1000);
    analogWrite(gear1, 0);
    analogWrite(gear2, 0);
    analogWrite(gear3, 0);
    analogWrite(gear4, 0);
    }
    if (software_press_lang == 3) {
    analogWrite(gear1, 0);
    analogWrite(gear2, 0);
    analogWrite(gear3, 0);
    analogWrite(gear4, 0);
    }
    else if (software_press_lang == 2) {
    while (count > 0) {
      analogWrite(gear1, 0);
      analogWrite(gear2, 100);
      analogWrite(gear3, 0);
      analogWrite(gear4, 100);
      count--;
    }
    analogWrite(gear1, 0);
    analogWrite(gear2, 0);
    analogWrite(gear3, 0);
    analogWrite(gear4, 0);
    }
    else if (software_press_lang == 1 && count < 7) {
    count++;
    analogWrite(gear1, 100);
    analogWrite(gear2, 0);
    analogWrite(gear3, 100);
    analogWrite(gear4, 0);
    pinMode(trig, OUTPUT);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(5);
    digitalWrite(trig, LOW);
    pinMode(echo, INPUT);
    duration_mushroom = pulseIn(echo, HIGH);
    dis_mushroom = ((duration_mushroom / 29) / 2);
    analogWrite(gear1, 0);
    analogWrite(gear2, 0);
    analogWrite(gear3, 0);
    analogWrite(gear4, 0);
    }
    else if (software_press_lang == 0 && count > 0) {
    while (count > 0) {
      analogWrite(gear1, 0);
      analogWrite(gear2, 100);
      analogWrite(gear3, 0);
      analogWrite(gear4, 100);
      count--;
    }
    analogWrite(gear1, 0);
    analogWrite(gear2, 0);
    analogWrite(gear3, 0);
    analogWrite(gear4, 0);
    }
    else if (software_press_lang == 0 && count <= 4) {
    while (count <= 4) {
      count++;
      analogWrite(gear1, 100);
      analogWrite(gear2, 0);
      analogWrite(gear3, 100);
      analogWrite(gear4, 0);
      delayMicroseconds(2);
      digitalWrite(trig, HIGH);
      delayMicroseconds(5);
      digitalWrite(trig, LOW);
      pinMode(echo, INPUT);
      duration_mushroom = pulseIn(echo, HIGH);
      dis_mushroom = ((duration_mushroom / 29) / 2);
      delay(1000);
      analogWrite(gear1, 0);
      analogWrite(gear2, 0);
      analogWrite(gear3, 0);
      analogWrite(gear4, 0);
    }
    }*/
}
