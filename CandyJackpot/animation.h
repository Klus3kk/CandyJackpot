#pragma once
#include <Adafruit_SSD1306.h>
#include "symbols.h"

extern Adafruit_SSD1306 display;
extern int slotResults[3];
extern const unsigned char* symbolBitmaps[];
extern const int numSymbols;

// Display configuration
const int DISPLAY_SYMBOL_SIZE = 16;


void displaySplashScreen() {
  // This function shows the splash screen with CANDY JACKPOT centered
  // and scrolling "PULL LEVER TO PLAY" text
  
  display.clearDisplay();
  
  // Title centered
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  
  // Calculate width of "CANDY" text (each char is ~12 pixels at size 2)
  int titleWidth = 5 * 12; // "CANDY" has 5 characters
  int startX = (128 - titleWidth) / 2;
  display.setCursor(startX, 5);
  display.println(F("CANDY"));
  
  // Calculate width of "JACKPOT" text (7 characters)
  titleWidth = 7 * 12;
  startX = (128 - titleWidth) / 2;
  display.setCursor(startX, 25);
  display.println(F("JACKPOT"));
  display.display();
  
  // Pause to show the title long enough (but exit early if button is pressed)
  unsigned long startTime = millis();
  while (millis() - startTime < 3000) {
    if (digitalRead(buttonPin) == LOW) {
      return; // Exit immediately if button is pressed
    }
    delay(10);
  }
  
  // Now add the scrolling text - continuous scrolling
  display.setTextSize(1);
  
  const char* scrollText = "PULL LEVER TO PLAY";
  int textWidth = strlen(scrollText) * 6; // Width of the text in pixels
  
  // Do continuous scrolling until button is pressed
  while (true) {
    // Check for button press before starting a new cycle
    if (digitalRead(buttonPin) == LOW) {
      return; // Exit immediately if button is pressed
    }
    
    // Scroll from right edge to left edge in one continuous motion
    for (int i = 128; i > -textWidth; i--) {
      // Check button during animation
      if (digitalRead(buttonPin) == LOW) {
        return; // Exit immediately if button is pressed
      }
      
      display.clearDisplay();
      
      // Redraw the title with each frame
      display.setTextSize(2);
      titleWidth = 5 * 12;
      startX = (128 - titleWidth) / 2;
      display.setCursor(startX, 5);
      display.println(F("CANDY"));
      
      titleWidth = 7 * 12;
      startX = (128 - titleWidth) / 2;
      display.setCursor(startX, 25);
      display.println(F("JACKPOT"));
      
      // Draw scrolling text
      display.setTextSize(1);
      display.setCursor(i, 50);
      display.println(scrollText);
      display.display();
      delay(15);
    }
  }
  
  // We should never reach here since the loop is infinite
  // and will only exit via the button press return statements
}

void initDisplay() {
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    // If display initialization fails, we should indicate this somehow
    // For now, we'll just halt
    for(;;);
  }
  display.clearDisplay();
  display.display();
  
  // Show splash screen
  displaySplashScreen();
}


void animateLeverPull() {
  // Visual feedback for lever pull
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  // Center the text
  int textWidth = 10 * 6; // "Here we go!" is ~10 chars
  int startX = (128 - textWidth) / 2;
  display.setCursor(startX, 28);
  display.println(F("Here we go!"));
  display.display();
  delay(1000); // Longer pause
}

void spinSlots() {
  // Spin animation, fast changing symbols
  for (int i = 0; i < 15; i++) {
    display.clearDisplay();
    
    // Randomize all slots
    for (int slot = 0; slot < 3; slot++) {
      int randomSymbol = random(numSymbols);
      // Position each symbol in its own "screen" section
      display.drawBitmap(10 + slot*40, 24, symbolBitmaps[randomSymbol], 
                        DISPLAY_SYMBOL_SIZE, DISPLAY_SYMBOL_SIZE, SSD1306_WHITE);
    }
    
    display.display();
    delay(100);
  }
}

void stopSlotSequentially() {
  // Stop each slot one by one with animation
  for (int slot = 0; slot < 3; slot++) {
    // Determine final result for this slot
    if (slot == 2 && slotResults[0] == slotResults[1]) {
      // For the last slot, decide if we force a win (1 in 3 chance)
      if (random(3) == 0) {
        slotResults[2] = slotResults[0]; // Force win
      } else {
        // Ensure no win by choosing a different symbol
        do {
          slotResults[2] = random(numSymbols);
        } while (slotResults[2] == slotResults[0]);
      }
    } else {
      // Random result for other slots
      slotResults[slot] = random(numSymbols);
    }
    
    // Spin a few more times before stopping
    for (int i = 0; i < 5; i++) {
      display.clearDisplay();
      
      // Draw stopped slots
      for (int j = 0; j <= slot; j++) {
        display.drawBitmap(10 + j*40, 24, symbolBitmaps[slotResults[j]], 
                          DISPLAY_SYMBOL_SIZE, DISPLAY_SYMBOL_SIZE, SSD1306_WHITE);
      }
      
      // Draw spinning slots
      for (int j = slot + 1; j < 3; j++) {
        int randomSymbol = random(numSymbols);
        display.drawBitmap(10 + j*40, 24, symbolBitmaps[randomSymbol], 
                          DISPLAY_SYMBOL_SIZE, DISPLAY_SYMBOL_SIZE, SSD1306_WHITE);
      }
      
      display.display();
      delay(100);
    }
    
    delay(700); // Longer pause after each slot stops
  }
}

void displayResult() {
  // Show final result on display
  display.clearDisplay();
  for (int slot = 0; slot < 3; slot++) {
    display.drawBitmap(10 + slot*40, 24, symbolBitmaps[slotResults[slot]], 
                      DISPLAY_SYMBOL_SIZE, DISPLAY_SYMBOL_SIZE, SSD1306_WHITE);
  }
  display.display();
}

bool checkWin() {
  // Win if all three symbols match
  return (slotResults[0] == slotResults[1] && slotResults[1] == slotResults[2]);
}

void displayWinMessage() {
  display.clearDisplay();
  for (int slot = 0; slot < 3; slot++) {
    display.drawBitmap(10 + slot*40, 24, symbolBitmaps[slotResults[slot]], 
                      DISPLAY_SYMBOL_SIZE, DISPLAY_SYMBOL_SIZE, SSD1306_WHITE);
  }
  display.setTextSize(1);
  // Center "WINNER!" text
  int textWidth = 7 * 6; // "WINNER!" is 7 chars
  int startX = (128 - textWidth) / 2;
  display.setCursor(startX, 45);
  display.println(F("WINNER!"));
  display.display();
}

void displayLoseMessage() {
  display.clearDisplay();
  for (int slot = 0; slot < 3; slot++) {
    display.drawBitmap(10 + slot*40, 24, symbolBitmaps[slotResults[slot]], 
                      DISPLAY_SYMBOL_SIZE, DISPLAY_SYMBOL_SIZE, SSD1306_WHITE);
  }
  display.setTextSize(1);
  // Center "TRY AGAIN!" text
  int textWidth = 10 * 6; // "TRY AGAIN!" is ~10 chars
  int startX = (128 - textWidth) / 2;
  display.setCursor(startX, 45);
  display.println(F("TRY AGAIN!"));
  display.display();
}

void playWinAnimation() {
  // Make winning symbols blink
  for (int i = 0; i < 8; i++) { // More blinks
    display.clearDisplay();
    
    // Only draw on even iterations (creates blinking effect)
    if (i % 2 == 0) {
      for (int slot = 0; slot < 3; slot++) {
        display.drawBitmap(10 + slot*40, 24, symbolBitmaps[slotResults[slot]], 
                          DISPLAY_SYMBOL_SIZE, DISPLAY_SYMBOL_SIZE, SSD1306_WHITE);
      }
    }
    
    display.display();
    delay(200);
  }
  
  // Show winner text
  displayWinMessage();
}

