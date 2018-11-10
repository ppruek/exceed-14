#include<Servo.h>
#include<dht.h>
Servo myservo;
//----------water-------
#define gear_fan1 2
#define gear_fan2 3
bool chk = false;
//----------fan---------

#define DHT11 2
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
#define trig 12
#define echo 13
short lv_water;
int duration_water;
//----------water-------
////////////////////////
#include<UnoWiFiDevEd.h>
#include<Wire.h>
#define CONNECTOR "rest"
#define SERVER_ADDR "172.20.10.7"
String writeAddr;
CiaoData data;
CiaoData command;
char readAddr[] = "/data/CEEDney";
char check;
//------------------------------------

void setup()
{
  Ciao.begin();
  Serial.begin(9400);
  myservo.attach(9);
  myservo.write(0);
  pinMode(trig, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(gear_fan1, OUTPUT);
  pinMode(gear_fan2, OUTPUT);
  DDRD = DDRD | 0B11110000;
  PORTD = PORTD & 0B0000011;
  myservo.attach(13);
  myservo.write(110);
}

void loop()
{
  dhtTemp = DHT.read11(DHT11);
  dhtHumid = DHT.read11(DHT11);
  temperature = (short) DHT.temperature;
  writeAddr = "/set.php?key=temperature&value=" + (String)temperature;
  data = Ciao.write(CONNECTOR, SERVER_ADDR, writeAddr);
  humidity = (short) DHT.humidity;
  writeAddr = "/set.php?key=humidity&value=" + (String)humidity;
  data = Ciao.write(CONNECTOR, SERVER_ADDR, writeAddr);

  command = Ciao.read(CONNECTOR, SERVER_ADDR, readAddr);
  check = command.get(2);
  if (check == 'a') {
    analogWrite(gear_fan1, 100);
    analogWrite(gear_fan2, 0);
  }
  else if (check == 'b') {
    analogWrite(gear_fan1, 0);
    analogWrite(gear_fan2, 0);
  }
  ///////////////////////////////////////////////////////
  command = Ciao.read(CONNECTOR, SERVER_ADDR, readAddr);
  check = command.get(2);
  if (check == 'c') {
    myservo.write(180);
  }
  else if (check == 'd') {
    myservo.write(110);
  }
  else if (humidity > 80 ) {
    chk = true;
    while (chk) {
      dhtHumid = DHT.read11(DHT11);
      humidity = (short) DHT.humidity;
      writeAddr = "/set.php?key=humidity&value=" + (String)humidity;
      data = Ciao.write(CONNECTOR, SERVER_ADDR, writeAddr);
      if (humidity < 80) { //80% of huminity of mushroom
        chk = false;
        break;
      }
      analogWrite(gear_fan1, 100);
      analogWrite(gear_fan2, 0);
    }
    analogWrite(gear_fan1, 0);
    analogWrite(gear_fan2, 0);
  }
  ///////////////////////////////////////////////////////
    if (check == 'g') {
    analogWrite(LED1, 255);
  }
  else if (check == 'h') {
    light_intensity = analogRead(LDR);
    writeAddr = "/set.php?key=light&value=" + (String)light_intensity;
    data = Ciao.write(CONNECTOR, SERVER_ADDR, writeAddr);
    analogWrite(LED1, 10);
    if (humidity < 10) { 
      analogWrite(LED1, 200);
    }
    else if (humidity < 30) {
      analogWrite(LED1, 100);
    }
    else {
      analogWrite(LED1, 10);
    }
  }
  
}



