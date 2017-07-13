#include <Adafruit_LiquidCrystal.h>//LCD LIBRARY
Adafruit_LiquidCrystal lcd(0);//CONNECTING TO i2C, DAT PIN #SDA & CLK PIN #SCL:

void setup() {
  lcd.begin(16, 2);
  lcd.setBacklight(HIGH);
  lcd.print("Hello, World!");
}

void loop() {
  // put your main code here, to run repeatedly:


