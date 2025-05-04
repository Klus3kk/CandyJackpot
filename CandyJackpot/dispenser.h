#pragma once
#include "config.h"
#include <Servo.h>

Servo dispenserServo;

void initDispenser() {
  dispenserServo.attach(dispenserServoPin);
  dispenserServo.write(DISPENSER_CLOSED);
  delay(300); // Give the servo time to reach position
}

void activateDispenser() {
  // Open dispenser gradually
  for (int pos = DISPENSER_CLOSED; pos <= DISPENSER_OPEN; pos += 5) {
    dispenserServo.write(pos);
    delay(20);
  }
  
  // Keep dispenser open longer to allow candy to fall
  delay(2000);
  
  // Close dispenser gradually
  for (int pos = DISPENSER_OPEN; pos >= DISPENSER_CLOSED; pos -= 5) {
    dispenserServo.write(pos);
    delay(20);
  }
}