#define gear_water1 4
#define gear_water2 5
#define gear_water3 6
#define gear_water4 7

#include<Wire.h>
#include<UnoWiFiDevEd.h>
#define CONNECTOR "rest"
#define SERVER_ADDR "158.108.165.223"
String writeAddr;
String readAddr = "/data/CEEDney/order/";
CiaoData data;
String WORD0 = "";
String WORD1 = "";

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void setup() {
  Ciao.begin();
  Serial.begin(9600);
  pinMode(gear_water1, OUTPUT);
  pinMode(gear_water2, OUTPUT);
  pinMode(gear_water3, OUTPUT);
  pinMode(gear_water4, OUTPUT);
}

void loop() {
  data = Ciao.read(CONNECTOR, SERVER_ADDR, readAddr);
  WORD0 = getValue(String(data.get(2)), '-' , 0);
  Serial.print(WORD0);
  if (WORD0 == "0") {
    run_right(gear_water1, gear_water2);
    run_right(gear_water3, gear_water4);
    run_stop(gear_water1, gear_water2);
    run_stop(gear_water3, gear_water4);
    delay(3000);
  }
}

void run_right(int a, int b) {
  analogWrite(a, 200);
  analogWrite(b, 0);
  }

void run_stop(int a, int b) {
  analogWrite(a, 0);
  analogWrite(b, 0);
}

