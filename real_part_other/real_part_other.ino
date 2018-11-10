#include<Servo.h>
#include<dht.h>
Servo myservo;
//----------water-------
#define gear_fan1 6
#define gear_fan2 7
bool chk = false;
//----------fan---------

#define DHT11 4
dht DHT;
short dhtTemp;
short dhtHumid;
short temperature;
short humidity;
//----------temp--------
#define LDR A0
#define LED1 8
short light_intensity;
//----------light-------
#define trig 3
#define echo 2
short lv_water;
int duration_water;
//----------water-------
////////////////////////
#include<UnoWiFiDevEd.h>
#include<Wire.h>
#define CONNECTOR "rest"
#define SERVER_ADDR "158.108.165.223"
String writeAddr;
CiaoData data;
CiaoData command;
char readAddr[] = "/data/CEEDney/order/";
//------------------------------------
//158.108.165.223/data/CEEDney/order
void setup()
{
  Ciao.begin();
  Serial.begin(9400);
  pinMode(trig, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(gear_fan1, OUTPUT);
  pinMode(gear_fan2, OUTPUT);
  DDRD = DDRD | 0B11110000;
  PORTD = PORTD & 0B0000011;
  myservo.attach(10);
  myservo.write(90);
}

void loop()
{
  command = Ciao.read(CONNECTOR, SERVER_ADDR, readAddr);
  dhtTemp = DHT.read11(DHT11);
  dhtHumid = DHT.read11(DHT11);
  temperature = (short) DHT.temperature;
  writeAddr = "/data/CEEDney/temperature/set/" + (String)temperature;
  Serial.println(temperature);
  data = Ciao.write(CONNECTOR, SERVER_ADDR, writeAddr);
  humidity = (short) DHT.humidity;
  writeAddr = "/data/CEEDney/humidity/set/" + (String)humidity;
  Serial.println(humidity);
  data = Ciao.write(CONNECTOR, SERVER_ADDR, writeAddr);
  light_intensity = analogRead(LDR);
  writeAddr = "/data/CEEDney/light/set/" + (String)light_intensity;
  Serial.println(light_intensity);
  data = Ciao.write(CONNECTOR, SERVER_ADDR, writeAddr);
  if (command.get(2) != 'z') {
    command = Ciao.read(CONNECTOR, SERVER_ADDR, readAddr);
    char *check = command.get(2);
    Serial.println(check);
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
      myservo.write(110);
    }
    else if (check == 'd') {
      myservo.write(180);
    }
    else if (humidity > 80 ) {
      chk = true;
      while (chk) {
        dhtHumid = DHT.read11(DHT11);
        humidity = (short) DHT.humidity;
        writeAddr = "/data/CEEDney/humidity/set/" + (String)humidity;
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
    data = Ciao.write(CONNECTOR, SERVER_ADDR, "/data/CEEDney/order/set/z");
  }
}



