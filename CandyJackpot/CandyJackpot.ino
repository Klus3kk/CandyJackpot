#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "config.h"
#include "bitmaps.h"
#include "symbols.h"
#include "animation.h"
#include "lever.h"
#include "sound.h"
#include "dispenser.h"
#include "hand.h"

// Create display object
Adafruit_SSD1306 display(128, 64, &Wire, -1);
int slotResults[3];

// Track if we're in splash screen mode
//bool inSplashScreen = true;

// State machine
enum GameState {
  SPLASH,
  IDLE,
  LEVER_ANIM,
  SPIN,
  STOP_SLOTS,
  RESULT,
  WIN,
  LOSE,
  RESET
};

GameState state = SPLASH;
unsigned long stateStartTime = 0;
bool win = false;

void setup() {
  Serial.begin(9600);
  
  // Initialize components
  initConfig();
  initDisplay(); // This calls displaySplashScreen() internally
  initButton();
  initSound();
  
  // Commented out for initial testing
  initHand();
  initDispenser();
}

void loop() {
  // Update sound effects (needed for continuous sounds)
  //updateSpinSound();
  
  switch (state) {
    case SPLASH:
      displaySplashScreen();
      state = IDLE;
      break;

    case IDLE:
      if (buttonPressed()) {
        // When button is pressed, run the game
        //startSpinSound();
        state = LEVER_ANIM;
        stateStartTime = millis();
      }
      break;

    case LEVER_ANIM:
      // Show lever pull animation
      animateLeverPull();
      state = SPIN;
      break;

    case SPIN:
      spinSlots();
      state = STOP_SLOTS;
      break;

    case STOP_SLOTS:
      stopSlotSequentially(); 
      state = RESULT;
      stateStartTime = millis();
      break;

    case RESULT:
      displayResult();
      win = checkWin();
      stateStartTime = millis();
      state = win ? WIN : LOSE;
      break;

    case WIN:
      if (millis() - stateStartTime > 500) {
        playWinAnimation();
        playWinSound();
        thumbsUp();           // Show thumbs up with hand servo
        activateDispenser();  // Dispense candy
        stateStartTime = millis();
        state = RESET;
      }
      break;
    
    case LOSE:
      if (millis() - stateStartTime > 500) {
        displayLoseMessage();
        playLoseSound();
        thumbsDown();         // Show thumbs down with hand servo
        stateStartTime = millis();
        state = RESET;
      }
      break;

    case RESET:
      if (millis() - stateStartTime > 3000) {
        display.clearDisplay();
        display.display();
        displaySplashScreen();
        state = IDLE;
      }
      break;
  }
}