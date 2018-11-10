#define trig 3
#define echo 2
short lv_water;
int duration_water;

#include<UnoWiFiDevEd.h>
#include<Wire.h>
#define CONNECTOR "rest"
#define SERVER_ADDR "158.108.165.223"
String writeAddr;
CiaoData data;
CiaoData command;
char readAddr[] = "/data/CEEDney/order/";

short dis_water;

void setup() {
  Ciao.begin();
  Serial.begin(9400);
  pinMode(trig, OUTPUT);
}

void loop() {
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig, LOW);
  pinMode(echo, INPUT);
  duration_water = pulseIn(echo, HIGH);
  //Serial.println(duration_water);
  dis_water = ((duration_water * 100) / 65 / 5);
  writeAddr = "/data/CEEDney/ultradis/set/" + (String)dis_water;
  data = Ciao.write(CONNECTOR, SERVER_ADDR, writeAddr);

}
