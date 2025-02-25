/*
First pass at getting input and output 
With one button wired to arduino r3 pin 12 and GND
*/

#include <LiquidCrystal_I2C.h>

// LCD and Button Setup
LiquidCrystal_I2C lcd(0x27, 20, 4);
const int buttonPin = 12;
bool lastButtonState = HIGH;
String text = "";  // Stores the text to display

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);

  pinMode(buttonPin, INPUT_PULLUP);  // Internal pull-up resistor enabled
}

void screenOut(String &text, bool buttonState) {
  // Detect button press (LOW means pressed)
  if (buttonState == LOW && lastButtonState == HIGH) {
    delay(50);                            // debounce
    if (digitalRead(buttonPin) == LOW) {  // Confirm still pressed
      text += 'A';                        // Add 'A' to the string

      // Update LCD
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(text);

      // Wait for button release to avoid rapid repeats
      while (digitalRead(buttonPin) == LOW)
        ;
      delay(50);  // Extra debounce after release
    }

    if (text.length() > 12) {  // If text sting longer than 12 characters reset.
      lcd.clear();
      lcd.setCursor(0, 0);
      text = "";  // Clear text 
    }
  }
  lastButtonState = buttonState;
}

// main loop
void loop() {
  bool buttonState = digitalRead(buttonPin);
  screenOut(text, buttonState);
}