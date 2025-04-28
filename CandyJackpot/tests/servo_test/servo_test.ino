#include <Servo.h>

int buttonPin = 2;
int servoPin = 9;
int servoPin2 = 10;

Servo servo1;
Servo servo2;
int angle = 0;  // servo position in degrees

void setup() {
  servo1.attach(servoPin);
  servo2.attach(servoPin2);
}

void loop() {
  // scan from 0 to 180 degrees
  for (angle = 0; angle <= 180; angle++) {
    servo1.write(angle);
    servo2.write(angle);
    delay(15);
  }

  // now scan back from 180 to 0 degrees
  for (angle = 180; angle >= 0; angle--) {
    servo1.write(angle);
    servo2.write(angle);
    delay(15);
  }
}
