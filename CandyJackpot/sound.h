#pragma once
#include "config.h"
#include <Adafruit_SSD1306.h>

static bool spinning = false;
static unsigned long lastToneTime = 0;
static int toneState = 0;  // 0: off, 1: on
static int tonesLeft = 6;

void initSound() {
    pinMode(speakerPin, OUTPUT);
}

void startSpinSound() {
    spinning = true;
    tonesLeft = 6;          // 3 bipy (on/off = 6 zmian)
    lastToneTime = millis();
    toneState = 0;
}

void updateSpinSound() {
    if (!spinning) return;
  
    if (millis() - lastToneTime >= 100) {
      if (toneState == 0) {
        tone(speakerPin, 1000);
        toneState = 1;
      } else {
        noTone(speakerPin);
        toneState = 0;
      }
  
      tonesLeft--;
      lastToneTime = millis();
  
      if (tonesLeft <= 0) {
        spinning = false;
        noTone(speakerPin);
      }
    }
}

void playWinSound() {
    for (int f = 500; f <= 1500; f += 100) {
        tone(speakerPin, f);
        delay(100);
      }
      noTone(speakerPin);
}
void playLoseSound() {
    for (int f = 1000; f >= 300; f -= 100) {
        tone(speakerPin, f);
        delay(150);
      }
      noTone(speakerPin);
}