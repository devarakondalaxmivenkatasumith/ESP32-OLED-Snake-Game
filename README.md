# ESP32 OLED Snake Game with Joystick Control

This project demonstrates how to build a classic Snake Game using an ESP32 DevKit V1, SH1106 OLED Display, and HW-504 Joystick Module. The player controls the snake using the joystick, collects food to increase the score, and avoids collisions with walls and its own body.

## Hardware Used

* ESP32 DevKit V1
* SH1106 OLED Display (128x64)
* HW-504 Joystick Module
* Breadboard
* Jumper Wires
* USB Cable

## Connections

### SH1106 OLED Display

| OLED Pin | ESP32 Pin |
| -------- | --------- |
| VCC      | 3.3V      |
| GND      | GND       |
| SDA      | GPIO21    |
| SCL      | GPIO22    |

### HW-504 Joystick Module

| Joystick Pin | ESP32 Pin |
| ------------ | --------- |
| VCC          | 3.3V      |
| GND          | GND       |
| VRX          | GPIO34    |
| VRY          | GPIO35    |
| SW           | GPIO32    |

## Features

* Snake Game on OLED Display
* Joystick-Based Direction Control
* Real-Time Score Tracking
* Random Food Generation
* Snake Growth Mechanism
* Wall Collision Detection
* Self-Collision Detection
* Game Over Screen
* Restart Using Joystick Button
* Embedded Graphics Programming
* ESP32 ADC Input Handling

## Working Principle

1. ESP32 initializes the OLED display and joystick inputs.
2. The joystick continuously provides direction commands.
3. The snake moves across the OLED screen.
4. Food is generated at random locations.
5. When the snake eats food, the score increases.
6. The snake length grows after each food item collected.
7. Collision with walls or the snake's own body ends the game.
8. Pressing the joystick button restarts the game.

## Arduino Libraries

* Adafruit GFX Library
* Adafruit SH110X Library
* Wire Library
* Arduino Core for ESP32

## Code

Upload the Arduino sketch to the ESP32 DevKit V1 using Arduino IDE.

## Applications

* Embedded Systems Learning
* OLED Display Interfacing
* Joystick Control Projects
* Game Development on Microcontrollers
* ESP32 Programming Practice
* Electronics and IoT Education
* Real-Time Embedded Graphics

## Learning Outcomes

* ESP32 GPIO Programming
* Analog Input Reading using ADC
* OLED Graphics Rendering
* Collision Detection Logic
* Game State Management
* Embedded C++ Programming
* Hardware Interfacing and Debugging

## Author

**Nova**

ECE Student | Embedded Systems & IoT Enthusiast
