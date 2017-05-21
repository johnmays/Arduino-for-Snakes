/*this program is written for the Uno, atleast for now because the 3.3v feather
 * isn't going to work with my damn 5v LCD, so I'll have to cut open a power
 * cord later to get that 5v.
*/

#include <Adafruit_LiquidCrystal.h>//LCD LIBRARY

Adafruit_LiquidCrystal lcd(0);//CONNECTING TO i2C, DAT PIN #6:

//GLOBALS:
int hours = 12;
int minutes = 0;
int seconds = 0;
bool am = true;
bool whichFlash = true;
bool on = true;
int flashTime = 4;//SECONDS

int onHours = 6;
int onMinutes = 30;
int onAM = true;
int offHours = 6;
int offMinutes = 30;
int offAM = false;

void setup(){
  lcd.begin(16, 2);
  lcd.setBacklight(HIGH);
  lcd.print("hello, world!");
  delay(2000);
}

void loop(){
  calculateTime();
  calculateRelayState();
  if(whichFlash == true){
    flashOne();  
  }else{
    flashTwo();  
  }
  delay(flashTime * 1000);//IN MILLIS
  seconds = seconds + flashTime;
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
  lcd.print(offHours);
  lcd.print(":");
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
  if(hours = 12){//WILL HAVE TO ADD 1 TO HOURS LATER TO NORMALIZE IT{1:00 --> 12:59}
    hours = 0;
    if(am == true){
      am = false;
    }else{
      am = true;
    }
  }
  
}
void calculateRelayState(){
  /*THIS FUNCTION SHOULD CHECK TO SEE WHEN THE TIME IS IN THE ON RANGE/ OFF RANGE AND CHANGE THE
   * RELAY STATE ACCORDINGLY
   */
                //THIS IS WHERE I AM
                //THIS IS WHERE I AM
                //THIS IS WHERE I AM
                //THIS IS WHERE I AM
                //THIS IS WHERE I AM
                //THIS IS WHERE I AM
                //THIS IS WHERE I AM

  
}
