/*
  Home Brew MicroController Computer
  Convert 8 bits to ASCII output

  Following the Arduino Style Guide for consistency:
  https://docs.arduino.cc/learn/contributions/arduino-writing-style-guide/

*/

#include <LiquidCrystal_I2C.h>

// =========================
// Constants and Globals
// =========================
LiquidCrystal_I2C lcd(0x27, 20, 4);
String text = "";        // Stores the binary input (8 bits at a time)
String asciiOutput = ""; // Holds ASCII output

// Button Class
class Button {
 private:
  int pin;
  bool lastState;
  void (*onPress)();

 public:
  Button(int p, void (*handler)()) : pin(p), lastState(HIGH), onPress(handler) {
    pinMode(pin, INPUT_PULLUP);
  }

  void check() {
    bool currentState = (digitalRead(pin) == LOW);
    if (currentState && lastState == HIGH) {
      delay(50); // Debounce
      if (onPress) onPress();
      waitForRelease();
    }
    lastState = currentState;
  }

  void waitForRelease() {
    while (digitalRead(pin) == LOW);
    delay(50);
  }
};

// Function Declarations
void addOne();
void addZero();
void clearScreen();
void clearASCII();
void binToChar();
void showFullMessage();
void updateLCD(const String &text);

// Create Button Objects (Global Scope)
Button buttonClear(13, clearScreen); // Clear screen and ASCII 
Button buttonOne(7, addOne);
Button buttonZero(2, addZero);
Button buttonConvert(12, binToChar);   // Convert 8-bit input to ASCII
Button buttonFullMsg(8, showFullMessage); // Show full ASCII message

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
  buttonClear.check();
  buttonOne.check();
  buttonZero.check();
  buttonConvert.check();
  buttonFullMsg.check();
}

// =========================
// Button Actions
// =========================

void addOne() {
  if (text.length() < 8) {  //Limit input to 8 bits
    text += "1";
    updateLCD(text);
  }
}

void addZero() {
  if (text.length() < 8) {  //Limit input to 8 bits
    text += "0";
    updateLCD(text);
  }
}

void clearScreen() {
  text = "";
  updateLCD("Cleared");
  clearASCII(); 
}

void clearASCII() {
  asciiOutput = "";
  updateLCD("ASCII Reset");
}

void binToChar() {
  if (text.length() == 8) {
    char asciiChar = (char)strtol(text.c_str(), nullptr, 2);
    asciiOutput += asciiChar;  // Append to full message

    updateLCD(String(asciiChar));  // Show only the current character
    text = "";  // Reset binary input for the next byte
  }
}

void showFullMessage() {
  updateLCD(asciiOutput);  // Display full ASCII message
}

// =========================
// Helper Functions
// =========================
void updateLCD(const String &text) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(text);
}
