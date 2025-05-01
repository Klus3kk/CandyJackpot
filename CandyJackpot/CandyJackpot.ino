#include "config.h"
#include "animation.h"
#include "symbols.h"
#include "lever.h"
#include "dispenser.h"
#include "sound.h"

// void setup() {
//   initConfig();
//   initDisplay();
//   initLever();
//   initDispenser();
//   initSound();
// }

// void loop() {
//   if (isLeverPulled()) {
//     playLeverAnimation();
//     spinSlots();
//     displayResult();
//     checkWin();
//   }
// }

// For now, testing the screen 
Adafruit_SSD1306 display(128, 64, &Wire, -1);
int slotResults[3];

void setup() {
  initDisplay();
  initButton();
  // other init
}

void loop() {
  if (buttonPressed()) {
    spinSlots();
    displayResult();
    delay(1000);
  }
}