void setup() {
  // put your setup code here, to run once:
  DDRD = DDRD | 0B11110000;
  PORTD = PORTD & 0B0000011;

  PORTD = PORTD | 0B10100000;
  delay(2000);
  // to stop
  PORTD = PORTD & 0B00000011;
  delay(1000);
  // another direction
  PORTD = PORTD | 0B01010000;
  delay(2000);
  PORTD = PORTD & 0B00000011;
}

void loop() {
  return;
  // put your main code here, to run repeatedly:
  PORTD = PORTD | 0B10100000;
  delay(2000);
  // to stop
  PORTD = PORTD & 0B00000011;
  delay(1000);
  // another direction
  PORTD = PORTD | 0B01010000;
  delay(2000);
}
