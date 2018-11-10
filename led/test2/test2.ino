#define LED 5
void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  pinMode(LED, OUTPUT);
  //digitalWrite(LED,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(LED, 200);   // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
  analogWrite(LED, 0);    // turn the LED off by making the voltage LOW
  delay(500);
}
