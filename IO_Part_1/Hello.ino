/*
wired to arduino r3:
I2C LCD | Arduino
    GND -> GND
    VCC -> 5V
    SDA -> A4
    SCL -> A5
*/

#include <LiquidCrystal_I2C.h>

// set up
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  // lcd set up
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1, 0);
}

void screenOut(String text) {
  for (int i = 0; i < text.length(); i++) {
    lcd.setCursor(i, 0);
    lcd.print(text[i]);
    delay(500);  // Adjust the delay time as needed
  }
  lcd.clear();
  delay(1000);  // Wait before restarting the loop
}

void loop() {
  String text = "Hello";
  screenOut(text);
}