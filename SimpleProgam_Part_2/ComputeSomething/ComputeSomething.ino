/*
  Home Brew MicroController Computer
  Convert 8 bits to ASCII ouput

  Following the Arduino Style Guide for consistency:
  https://docs.arduino.cc/learn/contributions/arduino-writing-style-guide/

*/

#include <LiquidCrystal_I2C.h>

// =========================
// Constants and Globals
// =========================
LiquidCrystal_I2C lcd(0x27, 20, 4);
String text = "";  // Stores the text to display

// Button Class
class Button {
 private:
  int pin;
  bool lastState;
  void (*onPress)();

 public:
  // Constructor
  Button(int p, void (*handler)()) : pin(p), lastState(HIGH), onPress(handler) {
    pinMode(pin, INPUT_PULLUP);
  }

  // Method to check and handle button press
  void check() {
    bool currentState = (digitalRead(pin) == LOW);
    if (currentState && lastState == HIGH) {
      delay(50);               // Debounce
      if (onPress) onPress();  // Call assigned action
      waitForRelease();
    }
    lastState = currentState;
  }

  // Wait for button release with debounce
  void waitForRelease() {
    while (digitalRead(pin) == LOW);
    delay(50);
  }
};

// Function Declarations
void addCharacter();
void clearScreen();
void addOne();
void addZero();
void updateLCD(const String &text);
void waitForRelease(int pin);
void handleButtons();

// =========================
// Setup Function
// =========================
void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Ready");
}

// =========================
// Main Loop
// =========================
void loop() {
  // Create Button Objects
  Button buttonA(12, binToChar);
  Button buttonClear(13, clearScreen);
  Button buttonOne(7, addOne);
  Button buttonZero(2, addZero);

  buttonA.check();
  buttonClear.check();
  buttonOne.check();
  buttonZero.check();
}

// =========================
// Button Actions
// =========================

void clearScreen() {
  text = "";
  updateLCD(text);
}

void addOne() {
  text += "1";
  updateLCD(text);
}

void addZero() {
  text += "0";
  updateLCD(text);
}

void binToChar() {
  String asciiOutput = "";

  // Ensure input length is a multiple of 8
  if (text.length() % 8 != 0) {
    updateLCD("Invalid Input");
    return;
  }

  for (int i = 0; i < text.length(); i += 8) {
    String byteStr = text.substring(i, i + 8);

    // strtol() function converts the string in \c nptr to a long value
    char asciiChar = (char)strtol(byteStr.c_str(), nullptr, 2);
    asciiOutput += asciiChar;
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  updateLCD(asciiOutput);
}

// =========================
// Helper Functions
// =========================
void updateLCD(const String &text) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(text);
}
