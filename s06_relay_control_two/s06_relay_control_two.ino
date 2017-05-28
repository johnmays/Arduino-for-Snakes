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

const int flashTime = 5; //NUMBER OF SECONDS THE DISPLAY SHOULD FLASH ONE SCREEN OR ANOTHER
//SHOULD BE FACTOR OF 60 EX: 2,3,4,5,6, FOR manageCurrentTime();

const int inputIncrement = 5;

unsigned long previousMillis = 0;

int curSeconds = 0;
int curMinutes = 0;
int curHours = 0;
bool curAM = true;

int onMinutes = 30;
int onHours = 6;
bool onAM = true;

int offMinutes = 30;
int offHours = 6;
bool offAM = false;

int relayPin = 2;
int powerSwitchPin = 4;
int upPin = 5;
int upSwitchState = 0;
int prevUpSwitchState = 0;

int downPin = 6;
int downSwitchState = 0;
int prevDownSwitchState = 0;

void setup() {
  lcd.begin(16, 2);
  lcd.setBacklight(HIGH);
  lcd.print("Hello, World!");
  delay(5000);

  pinMode(relayPin, OUTPUT);
  pinMode(powerSwitchPin, INPUT);
  pinMode(upPin, INPUT);
  pinMode(downPin, INPUT);
  digitalWrite(relayPin, HIGH);

}

void loop() {
  
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= flashTime*1000) {
    previousMillis = currentMillis;
    //EXECUTING FLASH BASED ON ASSIGNED [whichFlash] BOOL
    if(whichFlash == true){
      flashOne();
    } else {
      flashTwo();  
    }
    
    //ASSIGNING FLASH WITHOUT DELAY
    if (whichFlash == false) {
      whichFlash = true;
    } else {
      whichFlash = false;   
    }
    
    curSeconds = curSeconds + flashTime;
  }
  manageCurrentTime();
  manageRelayState();
  manageAllTimes();
}

void flashOne(){
//THIS FUNCTION SHOULD DISPLAY THE CURRENT TIME WHEN CALLED
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.print("TIME:");
  lcd.setCursor(0,1);
  lcd.print(curHours + 1);
  lcd.print(":");
  
  if(curMinutes < 10){
    lcd.print("0");
  }
  lcd.print(curMinutes);
}
void flashTwo(){
//THIS FUNCTION SHOULD DISPLAY THE ON/OFF TIMES WHEN CALLED
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.print(" ON: ");
  lcd.print(onHours);
  lcd.print(":");
  if(onMinutes < 10){
    lcd.print("0");
  }
  lcd.print(onMinutes);
  if(onAM == true){
    lcd.print("AM");  
  }else{
    lcd.print("PM");
  }
  lcd.setCursor(0,1);
  lcd.print("OFF: ");
  lcd.print(offHours);
  lcd.print(":");
  if(offMinutes < 10){
    lcd.print("0");
  }
  lcd.print(offMinutes);
  if(offAM == true){
    lcd.print("AM");  
  }else{
    lcd.print("PM");
  }
  
}
void manageCurrentTime(){

  if(curHours == 12){//HOURS AND PM/AM
    curHours = 0;
    if(curAM == true){
      curAM = false;
    }else{
      curAM = true;
    }
  }
  
  if(curMinutes == 60){//MINUTES:
    curMinutes = 0;
    curHours = curHours + 1;
  } 

  if(curSeconds == 60){//SECONDS:
    curSeconds = 0;
    curMinutes = curMinutes + 1;
  } 

}
void manageRelayState(){
  int switchState = digitalRead(powerSwitchPin);
  if(switchState == HIGH){//BUTTON IS CLOSED
    digitalWrite(relayPin, HIGH);
  }else{
    digitalWrite(relayPin, LOW);
  }
  
}
void manageAllTimes(){ 
  //THIS IS TEMPORARILY JUST FOR [curTime]
  upSwitchState = digitalRead(upPin);
  downSwitchState = digitalRead(upPin);
  if(upSwitchState != prevUpSwitchState){
    curMinutes = curMinutes + inputIncrement;
  }
  if(downSwitchState != prevDownSwitchState){
    curMinutes = curMinutes - inputIncrement;
  }
//THIS IS WHERE I AM THERE ARE ERRORS
//THIS IS WHERE I AM THERE ARE ERRORS
//THIS IS WHERE I AM THERE ARE ERRORS
//THIS IS WHERE I AM THERE ARE ERRORS
//THIS IS WHERE I AM THERE ARE ERRORS
//THIS IS WHERE I AM THERE ARE ERRORS
//THIS IS WHERE I AM THERE ARE ERRORS
//THIS IS WHERE I AM THERE ARE ERRORS
//THIS IS WHERE I AM THERE ARE ERRORS

  prevUpSwitchState = upSwitchState;
  prevDownSwitchState = downSwitchState;
}

