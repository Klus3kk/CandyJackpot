#pragma once
#include <Arduino.h>

// Random seed pin (unconnected analog pin for better randomness)
const int RANDOM_SEED_PIN = A0;

void initRandomizer() {
  // Initialize random number generator with noise from analog pin
  randomSeed(analogRead(RANDOM_SEED_PIN));
}

// Generate a random symbol index
int getRandomSymbol(int maxSymbols) {
  return random(maxSymbols);
}

// For testing: force a win occasionally
bool forceWin() {
  // 1 in 5 chance to force a win
  return (random(5) == 0);
}

// Function to randomize slots with possibility of forced win
void randomizeSlots(int slotResults[], int numSymbols, bool enableForcedWin = false) {
  if (enableForcedWin && forceWin()) {
    // Force all slots to have the same symbol
    int winningSymbol = random(numSymbols);
    for (int i = 0; i < 3; i++) {
      slotResults[i] = winningSymbol;
    }
  } else {
    // Standard random results for each slot
    for (int i = 0; i < 3; i++) {
      slotResults[i] = getRandomSymbol(numSymbols);
    }
  }
}