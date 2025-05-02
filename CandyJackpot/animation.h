#pragma once
#include <Adafruit_SSD1306.h>
#include "symbols.h"

extern Adafruit_SSD1306 display;
extern int slotResults[3];
extern const unsigned char* symbolBitmaps[];
extern const int numSymbols;

void displaySplashScreen() {
  // First, just show the title without any scrolling text
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  
  // Center "CANDY" and "JACKPOT"
  int candyWidth = 5 * 12;
  int candyX = (128 - candyWidth) / 2;
  display.setCursor(candyX, 5);
  display.print(F("CANDY"));
  
  int jackpotWidth = 7 * 12;
  int jackpotX = (128 - jackpotWidth) / 2;
  display.setCursor(jackpotX, 25);
  display.print(F("JACKPOT"));
  display.display();
  
  // Wait a bit
  unsigned long startTime = millis();
  while (millis() - startTime < 3000) {
    if (digitalRead(buttonPin) == LOW) {
      return;
    }
    delay(10);
  }
  
  // Now start the scrolling animation using drawChar instead of print
  const char* scrollText = "PULL LEVER TO PLAY";
  int textLen = strlen(scrollText);
  
  // Start from off-screen right
  int startPos = 128;
  
  // Keep scrolling until button press
  while (true) {
    if (digitalRead(buttonPin) == LOW) {
      return;
    }
    
    display.clearDisplay();
    
    // Draw fixed title
    display.setTextSize(2);
    display.setCursor(candyX, 5);
    display.print(F("CANDY"));
    display.setCursor(jackpotX, 25);
    display.print(F("JACKPOT"));
    
    // Draw scrolling text - character by character to avoid line wrapping
    display.setTextSize(1);
    for (int i = 0; i < textLen; i++) {
      int charX = startPos + (i * 6); // Each character is about 6 pixels wide at size 1
      // Only draw characters that are on the screen
      if (charX >= 0 && charX < 128) {
        display.drawChar(charX, 50, scrollText[i], SSD1306_WHITE, SSD1306_BLACK, 1);
      }
    }
    
    display.display();
    
    // Move text left
    startPos -= 2;
    
    // Reset position when it's completely off-screen
    if (startPos < -(textLen * 6)) {
      startPos = 128;
    }
    
    delay(15);
    
    // Check for button press again
    if (digitalRead(buttonPin) == LOW) {
      return;
    }
  }
}

void initDisplay() {
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    // If display initialization fails, halt
    for(;;);
  }
  display.clearDisplay();
  display.display();
  
  // Show splash screen
  displaySplashScreen();
}

// All the rest of your functions, updated to use centered symbol positions
void animateLeverPull() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  int textWidth = 10 * 6; // "Here we go!" is ~10 chars
  int startX = (128 - textWidth) / 2;
  display.setCursor(startX, 28);
  display.print(F("Here we go!"));
  display.display();
  delay(1000);
}

void spinSlots() {
  for (int i = 0; i < 15; i++) {
    display.clearDisplay();
    
    for (int slot = 0; slot < 3; slot++) {
      int randomSymbol = random(numSymbols);
      // Use centered positions
      int xPos = (slot == 0) ? FIRST_SYMBOL_X : 
                (slot == 1) ? SECOND_SYMBOL_X : THIRD_SYMBOL_X;
      
      display.drawBitmap(xPos, 24, symbolBitmaps[randomSymbol], 
                        DISPLAY_SYMBOL_SIZE, DISPLAY_SYMBOL_SIZE, SSD1306_WHITE);
    }
    
    display.display();
    delay(100);
  }
}

void stopSlotSequentially() {
  for (int slot = 0; slot < 3; slot++) {
    if (slot == 2 && slotResults[0] == slotResults[1]) {
      if (random(3) == 0) {
        slotResults[2] = slotResults[0]; // Force win
      } else {
        do {
          slotResults[2] = random(numSymbols);
        } while (slotResults[2] == slotResults[0]);
      }
    } else {
      slotResults[slot] = random(numSymbols);
    }
    
    for (int i = 0; i < 5; i++) {
      display.clearDisplay();
      
      // Draw stopped slots
      for (int j = 0; j <= slot; j++) {
        int xPos = (j == 0) ? FIRST_SYMBOL_X : 
                  (j == 1) ? SECOND_SYMBOL_X : THIRD_SYMBOL_X;
                  
        display.drawBitmap(xPos, 24, symbolBitmaps[slotResults[j]], 
                          DISPLAY_SYMBOL_SIZE, DISPLAY_SYMBOL_SIZE, SSD1306_WHITE);
      }
      
      // Draw spinning slots
      for (int j = slot + 1; j < 3; j++) {
        int randomSymbol = random(numSymbols);
        int xPos = (j == 0) ? FIRST_SYMBOL_X : 
                  (j == 1) ? SECOND_SYMBOL_X : THIRD_SYMBOL_X;
                  
        display.drawBitmap(xPos, 24, symbolBitmaps[randomSymbol], 
                          DISPLAY_SYMBOL_SIZE, DISPLAY_SYMBOL_SIZE, SSD1306_WHITE);
      }
      
      display.display();
      delay(100);
    }
    
    delay(700);
  }
}

void displayResult() {
  display.clearDisplay();
  for (int slot = 0; slot < 3; slot++) {
    int xPos = (slot == 0) ? FIRST_SYMBOL_X : 
              (slot == 1) ? SECOND_SYMBOL_X : THIRD_SYMBOL_X;
              
    display.drawBitmap(xPos, 24, symbolBitmaps[slotResults[slot]], 
                      DISPLAY_SYMBOL_SIZE, DISPLAY_SYMBOL_SIZE, SSD1306_WHITE);
  }
  display.display();
}

bool checkWin() {
  return (slotResults[0] == slotResults[1] && slotResults[1] == slotResults[2]);
}

void displayWinMessage() {
  display.clearDisplay();
  for (int slot = 0; slot < 3; slot++) {
    int xPos = (slot == 0) ? FIRST_SYMBOL_X : 
              (slot == 1) ? SECOND_SYMBOL_X : THIRD_SYMBOL_X;
              
    display.drawBitmap(xPos, 24, symbolBitmaps[slotResults[slot]], 
                      DISPLAY_SYMBOL_SIZE, DISPLAY_SYMBOL_SIZE, SSD1306_WHITE);
  }
  display.setTextSize(1);
  int textWidth = 7 * 6; // "WINNER!" is 7 chars
  int startX = (128 - textWidth) / 2;
  display.setCursor(startX, 45);
  display.print(F("WINNER!"));
  display.display();
}

void displayLoseMessage() {
  display.clearDisplay();
  for (int slot = 0; slot < 3; slot++) {
    int xPos = (slot == 0) ? FIRST_SYMBOL_X : 
              (slot == 1) ? SECOND_SYMBOL_X : THIRD_SYMBOL_X;
              
    display.drawBitmap(xPos, 24, symbolBitmaps[slotResults[slot]], 
                      DISPLAY_SYMBOL_SIZE, DISPLAY_SYMBOL_SIZE, SSD1306_WHITE);
  }
  display.setTextSize(1);
  int textWidth = 10 * 6; // "TRY AGAIN!" is ~10 chars
  int startX = (128 - textWidth) / 2;
  display.setCursor(startX, 45);
  display.print(F("TRY AGAIN!"));
  display.display();
}

void playWinAnimation() {
  // Phase 1: Blinking symbols (faster)
  for (int i = 0; i < 10; i++) {
    display.clearDisplay();
    
    if (i % 2 == 0) {
      for (int slot = 0; slot < 3; slot++) {
        int xPos = (slot == 0) ? FIRST_SYMBOL_X : 
                  (slot == 1) ? SECOND_SYMBOL_X : THIRD_SYMBOL_X;
                  
        display.drawBitmap(xPos, 24, symbolBitmaps[slotResults[slot]], 
                          DISPLAY_SYMBOL_SIZE, DISPLAY_SYMBOL_SIZE, SSD1306_WHITE);
      }
    }
    
    display.display();
    delay(100); // Faster blinks
  }
  
  // Phase 2: "Bouncing" symbols
  for (int bounce = 0; bounce < 3; bounce++) {
    // Move up
    for (int offset = 0; offset <= 10; offset += 2) {
      display.clearDisplay();
      for (int slot = 0; slot < 3; slot++) {
        int xPos = (slot == 0) ? FIRST_SYMBOL_X : 
                  (slot == 1) ? SECOND_SYMBOL_X : THIRD_SYMBOL_X;
                  
        display.drawBitmap(xPos, 24 - offset, symbolBitmaps[slotResults[slot]], 
                          DISPLAY_SYMBOL_SIZE, DISPLAY_SYMBOL_SIZE, SSD1306_WHITE);
      }
      display.display();
      delay(30);
    }
    
    // Move down
    for (int offset = 10; offset >= 0; offset -= 2) {
      display.clearDisplay();
      for (int slot = 0; slot < 3; slot++) {
        int xPos = (slot == 0) ? FIRST_SYMBOL_X : 
                  (slot == 1) ? SECOND_SYMBOL_X : THIRD_SYMBOL_X;
                  
        display.drawBitmap(xPos, 24 - offset, symbolBitmaps[slotResults[slot]], 
                          DISPLAY_SYMBOL_SIZE, DISPLAY_SYMBOL_SIZE, SSD1306_WHITE);
      }
      display.display();
      delay(30);
    }
  }
  
  // Phase 3: Growing/enlarging text effect
  const char* winText = "WINNER!";
  for (int size = 1; size <= 2; size++) {
    display.clearDisplay();
    
    // Draw the symbols
    for (int slot = 0; slot < 3; slot++) {
      int xPos = (slot == 0) ? FIRST_SYMBOL_X : 
                (slot == 1) ? SECOND_SYMBOL_X : THIRD_SYMBOL_X;
                
      display.drawBitmap(xPos, 24, symbolBitmaps[slotResults[slot]], 
                        DISPLAY_SYMBOL_SIZE, DISPLAY_SYMBOL_SIZE, SSD1306_WHITE);
    }
    
    // Draw text with increasing size
    display.setTextSize(size);
    int textWidth = strlen(winText) * 6 * size;
    int startX = (128 - textWidth) / 2;
    int startY = size == 1 ? 45 : 45;
    display.setCursor(startX, startY);
    display.print(winText);
    display.display();
    delay(500);
  }
  
  // Final display with sparkles/stars
  for (int i = 0; i < 10; i++) {
    display.clearDisplay();
    
    // Draw the symbols
    for (int slot = 0; slot < 3; slot++) {
      int xPos = (slot == 0) ? FIRST_SYMBOL_X : 
                (slot == 1) ? SECOND_SYMBOL_X : THIRD_SYMBOL_X;
                
      display.drawBitmap(xPos, 24, symbolBitmaps[slotResults[slot]], 
                        DISPLAY_SYMBOL_SIZE, DISPLAY_SYMBOL_SIZE, SSD1306_WHITE);
    }
    
    // Draw "WINNER!"
    display.setTextSize(1);
    int textWidth = 7 * 6;
    int startX = (128 - textWidth) / 2;
    display.setCursor(startX, 45);
    display.print(F("WINNER!"));
    
    // Draw random sparkles
    for (int stars = 0; stars < 5; stars++) {
      int x = random(128);
      int y = random(64);
      display.drawPixel(x, y, SSD1306_WHITE);
      display.drawPixel(x+1, y, SSD1306_WHITE);
      display.drawPixel(x, y+1, SSD1306_WHITE);
      display.drawPixel(x+1, y+1, SSD1306_WHITE);
    }
    
    display.display();
    delay(150);
  }
  
  // Final win message
  displayWinMessage();
}