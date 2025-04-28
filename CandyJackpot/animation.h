#pragma once
#include <Adafruit_SSD1306.h>
#include "symbols.h"

// Setup for display
extern Adafruit_SSD1306 display;
extern int slotResults[3];
extern const unsigned char* symbolBitmaps[];
extern const int numSymbols;


// Functions
void initDisplay() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
}

void spinSlots() {
  for (int i = 0; i < 15; i++) {
    for (int j = 0; j < 3; j++) {
      slotResults[j] = random(numSymbols);
    }

    display.clearDisplay();
    for (int j = 0; j < 3; j++) {
      display.drawBitmap(10 + j*40, 24, symbolBitmaps[slotResults[j]], 16, 16, SSD1306_WHITE);
    }
    display.display();
    delay(100);
  }
}

void displayResult() {
  display.clearDisplay();
  for (int j = 0; j < 3; j++) {
    display.drawBitmap(10 + j*40, 24, symbolBitmaps[slotResults[j]], 16, 16, SSD1306_WHITE);
  }
  display.display();
}
