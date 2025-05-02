#pragma once
#include "inttypes.h"
#include "randomizer.h"

// Pin Definitions
const uint8_t buttonPin = 2;        // Button/lever detection
const int speakerPin = 3;           // Sound output
const int dispenserServoPin = 9;    // Candy dispenser servo
const int leverServoPin = 10;

// Display settings
const int SCREEN_WIDTH = 128;       // OLED display width, in pixels
const int SCREEN_HEIGHT = 64;       // OLED display height, in pixels
const int SCREEN_ADDRESS = 0x3C;    // OLED I2C address

// Game timing configurations
const unsigned long debounceDelay = 50;  // Button debounce time in ms
const int spinAnimationDuration = 15;    // Number of frames for spinning animation
const int slotStopDelay = 500;           // Delay between slots stopping (ms)
const int winDisplayDuration = 3000;     // How long to show win message (ms)

// Servo positions
const int DISPENSER_CLOSED = 0;         // Servo position when dispenser is closed
const int DISPENSER_OPEN = 140;         // Servo position when dispenser is open
const int THUMBS_UP_POSITION = 180;     // Hand servo position for thumbs up
const int THUMBS_DOWN_POSITION = 0;     // Hand servo position for thumbs down
const int NEUTRAL_POSITION = 90;        // Hand servo neutral position

// Display configuration
const int DISPLAY_SYMBOL_SIZE = 16;

// Calculate positions to center the symbols horizontally
const int SCREEN_CENTER = 128 / 2;
const int SYMBOL_SPACING = 30;  // Space between symbols
const int FIRST_SYMBOL_X = SCREEN_CENTER - SYMBOL_SPACING - DISPLAY_SYMBOL_SIZE/2;
const int SECOND_SYMBOL_X = SCREEN_CENTER - DISPLAY_SYMBOL_SIZE/2;
const int THIRD_SYMBOL_X = SCREEN_CENTER + SYMBOL_SPACING - DISPLAY_SYMBOL_SIZE/2;


// Function to initialize configuration
void initConfig() {
  // Set pin modes
  pinMode(buttonPin, INPUT_PULLUP);
//   pinMode(speakerPin, OUTPUT);
  
  // Initialize random seed using noise from an unconnected analog pin
  initRandomizer();
  
  // Any other hardware-specific initialization can go here
}