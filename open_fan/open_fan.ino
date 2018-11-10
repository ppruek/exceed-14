#define motor1 6
#define motor2 7

void setup() {
  Serial.begin(9600);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  analogWrite(motor1, 200);
  analogWrite(motor2, 0); 
}

void loop(){
  
}

