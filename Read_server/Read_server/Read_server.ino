#include<Wire.h>
#include<UnoWiFiDevEd.h>
#define CONNECTOR "rest"
#define SERVER_ADDR "158.108.165.223"
char readAddr[] = "/data/CEEDney/order";
CiaoData data;
String WORD = "";

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void setup() {
  Ciao.begin();
  Serial.begin(9600);
}

void loop() {
  data = Ciao.read(CONNECTOR, SERVER_ADDR, readAddr);
  if(data.isEmpty()){
    Ciao.println("Failed");    
  }
  else{
    Serial.println(String(data.get(2)));
    WORD = getValue(String(data.get(2)), '-' , 2);
    Serial.println(WORD);
  }
  delay(1000);
}
