#define blue 10
#define yellow 11
#define green 12
#define sw 2
#define speak 5
bool chk = false;
void setup() {
  pinMode(blue, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(sw, INPUT);
  digitalWrite(blue,HIGH);
  digitalWrite(green,LOW);
  digitalWrite(yellow,LOW);
}

void loop() {
  
  int sww = digitalRead(sw);
  if(sww == 0){
    if(chk == false){
      digitalWrite(blue,LOW);
      digitalWrite(green,HIGH);
      analogWrite(speak,1);
      delay(1000);
      //if(sww == 0){
        chk = true;
      // }
    }
    else if(chk == true){
       digitalWrite(green,LOW);
       analogWrite(speak,0);
       digitalWrite(yellow,HIGH);
       delay(1000);
       digitalWrite(yellow,LOW);
       digitalWrite(blue,HIGH);
       //if(sww == 0){
         chk = false;
       //}
  }
  }
}
