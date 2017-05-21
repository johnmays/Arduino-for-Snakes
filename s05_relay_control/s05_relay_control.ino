/*this program is written for the Uno, atleast for now because the 3.3v feather
 * isn't going to work with my damn 5v LCD, so I'll have to cut open a power
 * cord later to get that 5v.
*/

#include <Adafruit_LiquidCrystal.h>//LCD LIBRARY

Adafruit_LiquidCrystal lcd(0);//CONNECTING TO i2C, DAT PIN #6:

//GLOBALS:
const int flashTime = 4;//SECONDS
int hours = 12;
int minutes = 0;
int seconds = 0;
bool am = true;
bool whichFlash = true;

int onHours = 6;
int onMinutes = 30;
int onAM = true;
int offHours = 6;
int offMinutes = 30;
int offAM = false;

bool relayOn = false;

const int backLightPin= 2;          //1
  int backLightSwitchState = 0;
  int prevBackLightSwitchState = 0;
const int downOffTimePin= 3;        //2
  int downOffTimeSwitchState = 0;
  int prevDownOffTimeSwitchState = 0;
const int downOnTimePin= 4;         //3
  int downOnTimeSwitchState = 0;
  int prevDownOnTimeSwitchState = 0;
const int upOffTimePin= 5;          //4
  int upOffTimeSwitchState = 0;
  int prevUpOffTimeSwitchState = 0;
const int upOnTimePin= 6;           //5
  int upOnTimeSwitchState = 0;
  int prevUpOnTimeSwitchState = 0;
const int downTimePin= 7;           //6
  int downTimeSwitchState = 0;
  int prevDownTimeSwitchState = 0;
const int upTimePin= 8;             //7
  int upTimeSwitchState = 0;
  int prevUpTimeSwitchState = 0;
const int manualSwitchPin= 9;       //8
  int manualSwitchSwitchState = 0;
  int prevManualSwitchSwitchState = 0;

const int timeIncrement = 5;

void setup(){
  lcd.begin(16, 2);
  lcd.setBacklight(HIGH);
  lcd.print("hello, world!");

  pinMode(backLightPin, INPUT);
  pinMode(downOffTimePin, INPUT);
  pinMode(downOnTimePin, INPUT);
  pinMode(upOffTimePin, INPUT);
  pinMode(upOnTimePin, INPUT);
  pinMode(downTimePin, INPUT);
  pinMode(upTimePin, INPUT);
  pinMode(manualSwitchPin, INPUT);
  delay(2000);
}

void loop(){
  handleInputs();
  handlePrevSwitchStates();
  calculateTime();
  calculateRelayState();
  if(whichFlash == true){
    flashOne();  
  }else{
    flashTwo();  
  }
  seconds = seconds + flashTime;
  
  
  delay(flashTime * 1000);//IN MILLIS
}

void flashOne(){
  //THIS WILL FLASH THE CURRENT TIME FOR [flashTime] SECONDS
  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print("TIME:");
  lcd.setCursor(0,1);
  lcd.print(hours + 1);
  lcd.print(":");
  if(minutes < 10){
    lcd.print("0");
    lcd.print(minutes);
  }else{//[minutes] IS TWO DIGITS
    lcd.print(minutes);
  }
  
  if(am == true){
    lcd.print(" AM");
  }else{
    lcd.print(" PM");
  }
  whichFlash = false;
}

void flashTwo(){
  //THIS WILL FLASH THE ON/OFF Times FOR [flashTime] SECONDS 
  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print("ON: ");
  lcd.print(onHours);
  lcd.print(":");
  lcd.print(onMinutes);
  if(onAM == true){
    lcd.print(" AM");
  }else{
    lcd.print(" PM");
  }
  lcd.setCursor(0,1); 
  lcd.print("OFF:");
  //lcd.print(offHours);
  lcd.print("6:");
  lcd.print(offMinutes);
  if(offAM == true){
    lcd.print(" AM");
  }else{
    lcd.print(" PM");
  }
  whichFlash = true;
}

void calculateTime(){
  //THIS FUNCTION WILL TRANSLATE ENDLESS MILLIS INTO A CLOCK FORMAT
  if(seconds >= 60){
    seconds = 0;
    minutes = minutes + 1;
  }
  if(minutes >= 60){
    minutes = 00;
    hours = hours + 1;
  }
  if(hours == 12){//WILL HAVE TO ADD 1 TO HOURS LATER TO NORMALIZE IT{1:00 --> 12:59}
    hours = 0;
    if(am == true){
      am = false;
    }else{
      am = true;
    }
  }
  if(upTimeSwitchState != prevUpTimeSwitchState){
    minutes = minutes + timeIncrement;
  }
  if(downTimeSwitchState != prevDownTimeSwitchState){
    minutes = minutes - timeIncrement;
  }
}
void calculateRelayState(){
  /*THIS FUNCTION SHOULD CHECK TO SEE WHEN THE TIME IS IN THE ON RANGE/ OFF RANGE AND CHANGE THE
   * RELAY STATE ACCORDINGLY
   */
  if(onHours == hours && onMinutes == minutes){
    relayOn = true;
  }else if(offHours = hours && offMinutes == minutes){
    relayOn = false;
  }
}
void handleInputs(){
  //THESE READ THE SWITCHES
  backLightSwitchState = digitalRead(backLightPin);
  downOffTimeSwitchState = digitalRead(downOffTimePin);
  downOnTimeSwitchState = digitalRead(downOnTimePin);
  upOffTimeSwitchState = digitalRead(upOffTimePin);
  upOnTimeSwitchState = digitalRead(upOnTimePin);
  downTimeSwitchState = digitalRead(downTimePin);
  upTimeSwitchState = digitalRead(upTimePin);
  manualSwitchSwitchState = digitalRead(manualSwitchPin);
}
void handlePrevSwitchStates(){
  //THESE ACCOUNT FOR PREV SWITCH STATE
  prevBackLightSwitchState = backLightSwitchState;
  prevDownOffTimeSwitchState = downOffTimeSwitchState;
  prevDownOnTimeSwitchState = downOnTimeSwitchState;
  prevUpOffTimeSwitchState = upOffTimeSwitchState;
  prevUpOnTimeSwitchState = upOnTimeSwitchState;
  prevDownTimeSwitchState = downTimeSwitchState;
  prevUpTimeSwitchState = upTimeSwitchState;
  prevManualSwitchSwitchState = manualSwitchSwitchState;  
}
