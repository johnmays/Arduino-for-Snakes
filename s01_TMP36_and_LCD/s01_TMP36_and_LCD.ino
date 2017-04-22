
//This is just a test with direct LCD input, an UNO, and a TMP36 sensor
#include <LiquidCrystal.h>//LCD Library
int tmpPin = 0;
LiquidCrystal lcd(12,11,5,4,3,2);//Inputs
int humidity = 000;
int tempCelsius = 00;
int tempFarenheit = 00;

void setup() {
  Serial.begin(9600);//Remember, there's no serial for trinkets
  lcd.begin(16,2);
  lcd.print("TEMP:60F 25C");
  lcd.setCursor(0,1);
  lcd.print("HUMIDITY: 80");
}

void loop() {
  //Update Values 
  int tmpValue = analogRead(tmpPin);
  float voltage = tmpValue * 5.0;
  voltage /= 1024.0;
  float tempCelsius = (voltage - 0.5) * 100 + 4.5;
  float tempFarenheit = (9/5)*tempCelsius + 32;
  Serial.print(voltage);
  Serial.print(" volts ");
  Serial.print(tempCelsius);
  Serial.print(" C ");
  Serial.print(tempFarenheit);
  Serial.print(" F ");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("TEMP:");
  lcd.print(int(tempFarenheit));
  lcd.print("F ");
  lcd.print(int(tempCelsius));
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("HUMIDITY:");
  lcd.print(humidity);
  lcd.print("%");
  delay(2000);
}
