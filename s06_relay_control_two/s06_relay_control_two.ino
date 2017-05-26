/* This program is for turning the light inside Cleopatra's snake cage on and off
 * Constantly managing the light is difficult, so why not get a computer that can
 * do it for me.  In theory, I would like to change backlight, have a manual on/off
 * switch and be able to shift around on/off and current times to my will.
 */

/* This program is written for a 5V Uno, running a relay(meant for a feather)
 * and an LCD, which should display current time and off/on times intermittently.
 */

#include <Adafruit_LiquidCrystal.h>//LCD LIBRARY

Adafruit_LiquidCrystal lcd(0);//CONNECTING TO i2C, DAT PIN #A5 & CLK PIN #A4:

bool whichFlash = true; //true = flashOne(); false = flashTwo();
const int flashTime = 3; //NUMBER OF SECONDS THE DISPLAY SHOULD FLASH ONE SCREEN OR ANOTHER

unsigned long previousMillis = 0;


void setup() {
  

}

void loop() {
  
  unsinged long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (whichFlash == false) {
      whichFlash = true;
    } else {
      whichFlash = false;   
    }
    
  }
  if(whichFlash == true){
    flashOne();
  } else {
    flashTwo();  
  }


}
