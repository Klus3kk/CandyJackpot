# CandyJackpot

**CandyJackpot** is a mini slot machine built with Arduino. It features an OLED display for symbol animation, a lever to start the spin, sound effects, and a servo-based candy dispenser for rewarding wins.

## Building and Running the Project

### Install Required Libraries

Before compiling, you must install the necessary libraries:

```bash
.\arduino-cli.exe lib install "Adafruit GFX Library"
.\arduino-cli.exe lib install "Adafruit SSD1306"
.\arduino-cli.exe lib install "Servo"
```

### Compile the Project

Once libraries are installed, compile the project with:

```bash
.\arduino-cli.exe compile --fqbn arduino:avr:uno --output-dir build .
```

### Run in Wokwi Simulator

The project is configured for simulation in Wokwi:

1. Open the project in VSCode
2. Start the Wokwi simulation
3. Click the button to test the slot machine functionality

## Project Components

- Arduino Uno ×1
- OLED Display 0.96'' 128x64 I2C ×1
- SG90 Servo Motors ×2
- Push Button ×1
- LEDs ×4
- Stereo Amplifier ×1
- 8 Ohm Speaker (missing, required)
- 5V Power Supply
- 6×AA Battery Holder
