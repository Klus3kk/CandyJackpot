#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "config.h"
#include "bitmaps.h"
#include "symbols.h"
#include "animation.h"
#include "lever.h"
// Commented out for initial testing
// #include "dispenser.h"
// #include "sound.h"

// Create display object
Adafruit_SSD1306 display(128, 64, &Wire, -1);
int slotResults[3];

// Track if we're in splash screen mode
bool inSplashScreen = true;

void setup() {
  Serial.begin(9600);
  
  // Initialize components
  initConfig();
  initDisplay(); // This calls displaySplashScreen() internally
  initButton();
  
  // Commented out for initial testing
  // initLever();
  // initDispenser();
  // initSound();
}

void loop() {
  if (buttonPressed()) {
    // When button is pressed, run the game
    
    // Show lever pull animation
    animateLeverPull();
    
    // Spin and stop slots
    spinSlots();
    stopSlotSequentially();
    
    // Show final result
    displayResult();
    delay(1000);
    
    // Check for win and display appropriate message
    if (checkWin()) {
      playWinAnimation();
    } else {
      displayLoseMessage();
    }
    
    // Wait before returning to splash screen
    delay(3000);
    
    // Simply clear the display and then call displaySplashScreen directly
    display.clearDisplay();
    display.display();
    displaySplashScreen();
  }
}