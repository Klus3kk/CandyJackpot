# CandyJackpot

**CandyJackpot** is a mini slot machine built with Arduino. It features an OLED display for symbol animation, a lever to start the spin, sound effects, and a servo-based candy dispenser for rewarding wins.

## Features
- Randomly spin and display three symbols
- Lever mechanism to trigger the slot spin
- Sound effects for winning and losing
- Candy dispenser activation on winning

## Components
- Arduino Uno ×1
- OLED Display 0.96'' 128x64 I2C ×1
- SG90 Servo Motors ×2
- Push Button ×1
- LEDs ×4
- Stereo Amplifier ×1
- 8 Ohm Speaker (missing, required)
- 5V Power Supply
- 6×AA Battery Holder

## Project Structure
- `CandyJackpot.ino` – main program
- `animation.h` – animation handling
- `symbols.h` – symbol definitions
- `lever.h` – lever control
- `dispenser.h` – candy dispenser logic
- `sound.h` – sound management
- `config.h` – pins and settings

## License
This project is licensed under the MIT License.
