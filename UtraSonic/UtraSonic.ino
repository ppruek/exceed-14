#define trig 10
#define echo 11

void setup() {
  Serial.begin(9600);
}

void loop() {
  long distance,duration;
  pinMode(trig,OUTPUT);
  //digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(5);
  digitalWrite(trig,LOW);
  pinMode(echo, INPUT);
  duration = pulseIn(echo,HIGH);
  //distance = ((duration/29)/2)/2.54;
  //Serial.println(distance);
  Serial.println(duration);
  delay(500);
}

