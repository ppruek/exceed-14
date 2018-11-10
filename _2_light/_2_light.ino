#define LDR A0
#define LED1 8
short light_intensity;

#include<UnoWiFiDevEd.h>
#include<Wire.h>
#define CONNECTOR "rest"
#define SERVER_ADDR "158.108.165.223"
String writeAddr;
CiaoData data;
CiaoData command;
char readAddr[] = "/data/CEEDney/order/";

void setup() {
  Ciao.begin();
  Serial.begin(9400);
  pinMode(LED1, OUTPUT);
  analogWrite(LED1, 200);
}

void loop() {
  light_intensity = analogRead(LDR);
  writeAddr = "/data/CEEDney/light/set/" + (String)light_intensity;
  Serial.println(light_intensity);
  data = Ciao.write(CONNECTOR, SERVER_ADDR, writeAddr);
  command = Ciao.read(CONNECTOR, SERVER_ADDR, readAddr);
  char *check = command.get(2);
  if (check == 'g') {
    analogWrite(LED1, 255);
  }
  else if (check == 'h') {
    analogWrite(LED1, 10);
    if (light_intensity < 100) {
      analogWrite(LED1, 200);
    }
    else if (light_intensity < 300) {
      analogWrite(LED1, 100);
    }
    else {
      analogWrite(LED1, 10);
    }
  }
}
