/*Reminder
 * had to instal USBTiny Drivers
 * had to change prgrammer to UsbTiny
 * had to change board to trinket 8 mHz
 * have reset with button on controller then press 'upload'
 */

/*
 *This is a sketch including the master code for my conditions monitoring project with the
 * Adafruit i2c/SPI LCD backpack
 * 16x2 Alphanumerical LCD
 * DHT22 Temp Sensor
 * 5V Logic Trinket
 *
 *PIN SETUP:
 * 5V to Trinket 5V pin
 * GND to Trinket GND pin
 * CLK to Trinket pin GPIO #2
 * DAT to Trinket pin GPIO #0
 */
 
//LIBRARIES:
#include <Adafruit_LiquidCrystal.h>
#include <TinyDHT.h>
#include <avr/power.h>      // needed to up clock to 16 MHz on 5v Trinket


//DHT22 TEMP SESNSOR CODE:
#define DHTTYPE DHT22
#define TEMPTYPE 0
#define DHTPIN 1   //meaning 1 kOhm resist(brown,black,red)
DHT dht(DHTPIN, DHTTYPE);


//CONNECTING TO i2C, DEFAUT PIN #0:
Adafruit_LiquidCrystal lcd(0);


//GLOBAL(S):
bool badRead = false;


void setup() {
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);//clocking stuff, to run at 16MHz
  //start LCD and Temp Sensor
  dht.begin();
  lcd.begin(16, 2);            
  lcd.setBacklight(HIGH);   //didn't know about backlight until now
}
 
void loop() {
  //must admit, is just copypaste for the DHT22 at this point, very confusing library
  int8_t h = dht.readHumidity();//humidity
  int16_t tc = dht.readTemperature(TEMPTYPE)-3;//temp
  float tf = tc*9/5 + 32;
  
  if(badRead == true){lcd.clear();}
  
  lcd.setCursor(0, 0); 
  if ( tc == BAD_TEMP || h == BAD_HUM ) { // if error conditions (see TinyDHT.h)
     lcd.print("Bad read on DHT");       //   print error message
     badRead = true;
  } else {
    lcd.setCursor(0,0);
    lcd.print("TEMP: ");
    lcd.print(int(tf));
    lcd.print("F ");
    lcd.print(int(tc));
    lcd.print("C ");
    lcd.setCursor(0,1);
    lcd.print("HUMIDITY: ");
    lcd.print(h);
    lcd.print("%");
    badRead = false;
  }
  delay(2000);
}
