#include<Servo.h>
Servo motor;
int times = 0;
void setup() {
  motor.attach(10);
  Serial.begin(9600);

}

void loop() {
  int ang;
  if (Serial.available()) {
    delay(100); //stability
    if (Serial.available() > 0) {
      ang = Serial.read();
      times = 0;

      if (ang == '0') {
        motor.write(90);
        if (times == 0) {
          Serial.println("90 degree");
          times = 1;
        }
      }

      else if (ang == '1') {
        motor.write(-90);
        if (times == 0) {
          Serial.println(" -90 degree");
          times = 1;
        }
      }
      else if ( ang == '2') {
        motor.write(180);
        if (times == 0) {
          Serial.println("180 degree");
          times = 1;
        }
      }
      else if ( ang == '3') {
        motor.write(-180);
        if (times == 0) {
          Serial.println(" -180 degree");
          times = 1;
        }
      }

    }

  }

}
