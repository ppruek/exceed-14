#define sw 5
#include "dht.h"
#define dht_apin A0
dht DHT;
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(sw, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  int sww = digitalRead(sw);
  if(sww == 0){
    DHT.read11(dht_apin);
    Serial.print("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println("C  ");
    delay(250);
  }
  //delay(1000);
}
