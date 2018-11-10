#include<dht.h>
#define DHT11 4
dht DHT;
short dhtTemp;
short dhtHumid;
short temperature;
short humidity;

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
}

void loop() {
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

}
