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
//SHOULD BE FACTOR OF 60 EX: 2,3,4,5,6, FOR manageCurrentTime();

unsigned long previousMillis = 0;

int curSeconds = 0;
int curMinutes = 0;
int curHours = 0;
bool curAM = true;


void setup() {
  lcd.begin(16, 2);
  lcd.setBacklight(HIGH);
  lcd.print("Hello, World!");
  delay(5000);

}

void loop() {
  manageCurrentTime;
  unsinged long currentMillis = millis();
//ASSIGNING FLASH WITHOUT DELAY
  if (currentMillis - previousMillis >= flashTime*1000) {
    previousMillis = currentMillis;

    if (whichFlash == false) {
      whichFlash = true;
    } else {
      whichFlash = false;   
    }
    curSeconds = curSeconds + flashTime;
  }
//EXECUTING FLASH BASED ON ASSIGNED [whichFlash] BOOL
  if(whichFlash == true){
    flashOne();
  } else {
    flashTwo();  
  }


}

void flashOne(){
//THIS FUNCTION SHOULD DISPLAY THE CURRENT TIME WHEN CALLED
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.print(curHours);

}
void flashTwo(){
//THIS FUNCTION SHOULD DISPLAY THE ON/OFF TIMES WHEN CALLED
  
}
void manageCurrentTime(){

  if(curSeconds == 60){//SECONDS:
    curSeconds = 0;
    curMinutes += 1;
  } 

  if(curMinutes == 60){//MINUTES:
    curMinutes = 0;
    curHours += 1;
  } 

  if(curHours == 12){//HOURS AND PM/AM
    curHours = 0;
    if(curAM == true){
      curAM = false;
    }else{
      curAM = true;
    }
  }
}
