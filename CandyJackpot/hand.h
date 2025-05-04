#pragma once
#include "config.h"
#include <Servo.h>

// Create a servo object for the hand
Servo handServo;

void initHand() {
  // Initialize the hand servo
  handServo.attach(leverServoPin);  // Using leverServoPin as defined in config.h
  
  // Set initial position (neutral)
  handServo.write(NEUTRAL_POSITION);
  delay(200); // Give servo time to reach position
}

// Animation for winning
void thumbsUp() {
  // Move hand to thumbs up position
  for (int pos = NEUTRAL_POSITION; pos <= THUMBS_UP_POSITION; pos += 5) {
    handServo.write(pos);
    delay(15);
  }
  delay(1000); // Hold position
  
  // Return to neutral
  for (int pos = THUMBS_UP_POSITION; pos >= NEUTRAL_POSITION; pos -= 5) {
    handServo.write(pos);
    delay(15);
  }
}

// Animation for losing
void thumbsDown() {
  // Move hand to thumbs down position
  for (int pos = NEUTRAL_POSITION; pos >= THUMBS_DOWN_POSITION; pos -= 5) {
    handServo.write(pos);
    delay(15);
  }
  delay(1000); // Hold position
  
  // Return to neutral
  for (int pos = THUMBS_DOWN_POSITION; pos <= NEUTRAL_POSITION; pos += 5) {
    handServo.write(pos);
    delay(15);
  }
}