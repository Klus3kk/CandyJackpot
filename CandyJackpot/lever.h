#pragma once
#include <Adafruit_SSD1306.h>

static bool lastState = HIGH;
static unsigned long lastDebounce = 0;
static const unsigned long debounceMs = 30;

void initButton() {
  pinMode(buttonPin, INPUT_PULLUP);
}

// returns true **once** with every button press.
bool buttonPressed() {
    bool pressed = false;
    if (digitalRead(buttonPin) == LOW) {
        pressed = true;
    }
    return pressed;
}
