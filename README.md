# Catch The Baton

This Arduino code allows you to build a fun game called "Catch The Baton" that tests reflexes and hand-eye coordination. Players try to catch batons electronically suspended by servo motors, which are then randomly released. It's a great game for parties, events, or team-building activities!

### Features

* Randomly releases batons at configurable intervals
* Multiple difficulty levels (Variant 3 only)
* Tracks which batons have been thrown
* Includes delays for resetting servos and starting rounds

### Hardware Required

* Arduino Uno or compatible board
* Servo motors (quantity matches the number of batons you want to include)
* Other electronic components and build equipment

### Software Required

* Arduino IDE ([https://support.arduino.cc/hc/en-us/articles/360019833020-Download-and-install-Arduino-IDE](https://support.arduino.cc/hc/en-us/articles/360019833020-Download-and-install-Arduino-IDE))

## Variants

This repository includes three variants of the code:

* **Variant 1:** Basic functionality with a fixed throwing interval.
* **Variant 2:** Introduces variable time intervals between releasing batons, making the game more challenging. 
* **Variant 3:** Most advanced variant with increasing difficulty. The throwing interval decreases after each round, with a delay between rounds.

## Instructions

1. **Install the Arduino IDE** if you haven't already.
2. Download or clone this repository.
3. Open the sketch for your desired variant (e.g., Variant_2.ino) in the Arduino IDE.
4. Install the required libraries.
5. Connect your servo motors to the Arduino board according to their pin assignments in the code. 
6. Upload the sketch to your Arduino board.
7. Open the serial monitor in the Arduino IDE (Tools > Serial Monitor) at 9600 baud.
8. The game will either start automatically after a delay or prompt you to press a button to begin.
9. When a baton is released, a message will be displayed on the serial monitor indicating which baton was thrown. 

## Simulation

Below are the links to simulations of the game:

* **Variant 1:** https://wokwi.com/projects/396526382099529729
* **Variant 2:** https://wokwi.com/projects/396553717576737793
* **Variant 3:** https://wokwi.com/projects/396526321998286849

### Customization

* You can modify the number of servos used (adjust `numServos` and `servoPins` arrays)
* Change the throwing interval (adjust the `batonInterval` variable) in variants 1 and 2.
* Adjust the delay times between rounds and servo resets in all variants.

### Notes

* Ensure that your servo motors are securely mounted and can move freely.
* You may need to modify the code for your specific hardware setup.
