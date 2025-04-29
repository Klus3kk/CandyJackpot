#pragma once
#include <Adafruit_SSD1306.h>

extern Adafruit_SSD1306 button;

static bool lastState = HIGH;
static unsigned long lastDebounce = 0;
static const unsigned long debounceMs = 30;

void initButton() {
  pinMode(buttonPin, INPUT_PULLUP);
}

// returns true **once** with every button press.
bool buttonPressed() {
  bool reading = digitalRead(buttonPin);
  bool pressed = false;

  // wykrycie zmiany stanu => restart licznika drgań
  if (reading != lastState) {
    lastDebounce = millis();
  }

  // jeśli stan stabilny dłużej niż debounceMs…
  if ((millis() - lastDebounce) > debounceMs) {
    // …i właśnie pojawiło się zbocze opadające (LOW) ⇒ przycisk wciśnięty
    if (reading == LOW && lastState == HIGH) {
      pressed = true;
    }
  }

  lastState = reading;
  return pressed;
}
