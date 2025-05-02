#pragma once
#include "config.h"
#include <Adafruit_SSD1306.h>

const int melody[] = { 440, 494, 523, 587, 659, 698, 784 };
const int noteDuration = 120;  // ms
const int numNotes = sizeof(melody) / sizeof(melody[0]);

int currentNote = 0;
unsigned long lastNoteTime = 0;
bool spinning = false;

void initSound() {
    pinMode(speakerPin, OUTPUT);
    noTone(speakerPin);
}

void startSpinSound() {
    currentNote = 0;
    lastNoteTime = millis();
    spinning = true;
    tone(speakerPin, melody[currentNote]);
  }
  
void updateSpinSound() {
    if (!spinning) return;
  
    if (millis() - lastNoteTime >= noteDuration) {
      currentNote++;
      lastNoteTime = millis();
  
      if (currentNote < numNotes) {
        tone(speakerPin, melody[currentNote]);
      } else {
        noTone(speakerPin);
        spinning = false;
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