#define trig  9
#define echo  10
#define gear1 4
#define gear2 5
#define gear3 6
#define gear4 7
short dis_mushroom;
int duration_mushroom;
short count = 0;
#include<UnoWiFiDevEd.h>
#include<Wire.h>
#define CONNECTOR "rest"
#define SERVER_ADDR "158.108.165.76"
String writeAddr;
CiaoData data;
CiaoData command;
char readAddr[] = "/data/CEEDney/order";
char check;
void setup()
{
  Ciao.begin();
  Serial.begin(9400);
  pinMode(gear1, OUTPUT);
  pinMode(gear2, OUTPUT);
  pinMode(gear3, OUTPUT);
  pinMode(gear4, OUTPUT);
  pinMode(trig, OUTPUT);
}
void loop()
{
  command = Ciao.read(CONNECTOR, SERVER_ADDR, readAddr);
  check = command.get(2);
  if (check == 'e') {
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(5);
    digitalWrite(trig, LOW);
    pinMode(echo, INPUT);
    duration_mushroom = pulseIn(echo, HIGH);
    writeAddr = "/data/CEEDney/ultradis/set/" + (String)duration_mushroom;
    data = Ciao.write(CONNECTOR, SERVER_ADDR, writeAddr);
    dis_mushroom = ((duration_mushroom / 29) / 2);
    PORTD = PORTD | 0B10100000;
    delay(800);
    PORTD = PORTD | 0B10100000;
    delay(2000);
  }
  else if(check == 'f'){
    PORTD = PORTD | 0B01010000;
    delay(800);
    PORTD = PORTD | 0B10100000;
    delay(2000);
  }
}

