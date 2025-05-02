#pragma once
#include "config.h"
#include <Servo.h>

Servo dispenserServo;

void initDispenser() {
    dispenserServo.attach(dispenserServoPin);
    dispenserServo.write(0);
}
void activateDispenser() {
    dispenserServo.write(90);
    delay(1000);
    dispenserServo.write(0);
}
