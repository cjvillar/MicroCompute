# Part 1: Setup, Input and Output.

Using a LiquidCrystal I2C with Arduino Uno.

[LiquidCrystal_I2C.h](https://github.com/johnrickman/LiquidCrystal_I2C)

| I2C LCD | Arduino |
|---------|---------|
| GND     | GND     |
| VCC     | 5V      |
| SDA     | A4      |
| SCL     | A5      |

The Hello.ino script test the output of a simple "Hello" program to ensure the I2C LCD is connected properly.

Eventually, I'll need a way to input data into the microcontroller so 
**InputTestOneButton.ino** is a first attempt at wiring up an input button and getting output to the screen. I use the [General-Purpose Input Output (GPIO)](https://www.electronicwings.com/arduino/digital-gpio-of-arduino) pin 12 as digital input, set with INPUT_PULLUP, which enables the built-in configurable pull-up resistor. 

With input and output on the screen, I think this is a good stopping point for Part 1. 

![Part1 in action: Arduino with LiquidCrystal_I2C and breadboard ](https://github.com/cjvillar/MicroCompute/blob/main/Part1/Part_1_io.png)

