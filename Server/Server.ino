#include<Wire.h>
#include<UnoWiFiDevEd.h>

const char CONNECTER[] = "rest";
const char SERVER_ADDR[] = "158.108.165.223";
const char writeAddr[] = "/data/CEEDney/order";
const char readAddr[] = "/data/CEEDney/order";

void setup() {
  Ciao.begin();
  Serial.begin(9600);
  Serial.println("HELLO WORLD!");
}

void loop() {
  CiaoData command = Ciao.write(CONNECTER, SERVER_ADDR, readAddr, "GET");
  const char *data = command.get(2);
  Serial.print("data: ");
  Serial.println(data);  
}
