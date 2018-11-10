#define gear1 4
#define gear2 5
#define gear3 6
#define gear4 7


//use for lotate to right

void setup()
{
  Serial.begin(9400);
  pinMode(gear1, OUTPUT);
  pinMode(gear2, OUTPUT);
  pinMode(gear3, OUTPUT);
  pinMode(gear4, OUTPUT);
  //pinMode(trig, OUTPUT);
  //delayMicroseconds(2);
  //digitalWrite(trig, HIGH);
  //delayMicroseconds(5);
  //digitalWrite(trig, LOW);
  //pinMode(echo, INPUT);
  //duration_mushroom = pulseIn(echo, HIGH);
  //dis_mushroom = ((duration_mushroom / 29) / 2);
  PORTD = PORTD | 0B01010000;
  delay(600);
  PORTD = PORTD | 0B10100000;
  delay(2000);
  PORTD = PORTD | 0B10100000;
  delay(600);
  PORTD = PORTD | 0B10100000;
  delay(2000);
}
void loop() {
  // put your main code here, to run repeatedly:

}
