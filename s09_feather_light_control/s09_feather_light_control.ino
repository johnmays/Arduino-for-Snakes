/* PROJECT SUMMARY: 
 * A project using the Adafruit Feather, 1x Relay Shield, and 16x2 LCD.
 * The feather operates the relay to keep a light on and off in between
 * the two times specified.  It displays those times and the current
 * time on an LCD for any sort of necessary checkup.
 */
 
/* CIRCUIT SUMMARY:
 * NOTE: Wing and Feather rest on a FeatherWing Doubler, effectively
 * connecting all necessary wires.
 * NOTE: Relay Control Pin is through Feather Pin [9]
 * LCD [VIn] to Feather [USB]
 * LCD [Gnd] to Feather [Gnd]
 * LCD [DAT] to Feather [SDA]
 * LCD [CLK] to Feather {SCL]
 */


#include <Adafruit_LiquidCrystal.h>//LCD LIBRARY

Adafruit_LiquidCrystal lcd(0);//CONNECTING TO i2C, DAT PIN #A5 & CLK PIN #A4:

unsigned long previousMillis = 0;
int previousProtoSwitchState = 0;

const int relayPin = 9;
const int protoSwitchPin = 10;
bool backlight = true;

//On at 9:00 AM
  const int onHours = 9;
  const int onMinutes = 00;
  const bool onAM = true;
//Off at 10:00 PM 
  const int offHours = 10;
  const int offMinutes = 00;
  const bool offAM = false;

int curHours = 0;
int curMinutes = 44;
int curSeconds = 00;
bool curAM = true;

void setup() {
  lcd.begin(16, 2);
  lcd.setBacklight(HIGH);
  backlight = true;
  lcd.clear();
  lcd.print("Hello, John");
  delay(2000);
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 1000) {
    previousMillis = currentMillis;
        
    curSeconds = curSeconds + 1;
    printToLCD();//FLASHES TOO MUCH ON A HIGHER REFRESH RATE, ( >240 Hz)
  }
  manageTime();
  //manageRelayState();
  manageBacklight();
}


void manageTime(){
  //PROGRESSING MINUTES:
  if(curSeconds == 60){
    curSeconds = 0;
    curMinutes = curMinutes + 1;
  }
  //PROGRESSING HOURS:
  if(curMinutes == 60){
    curMinutes = 0;
    curHours = curHours + 1; 
  }
  //PROGRESSING AM/PM:
  if(curHours == 12){
    curHours ==  0;//WE WILL ADD 1 TO [curHours] BECAUSE TIME PROGRESSES FROM 1:00 TO 12:59.
    if(curAM == true){
      curAM = false;
    }else{
      curAM = true;
    }
  }
    
}
void printToLCD(){
 //LINE 1: 
  lcd.clear();
  lcd.print("IT IS ");
  lcd.print(curHours + 1);
  lcd.print(":");
  if(curMinutes < 10){
    lcd.print("0");//WANT TO PRINT '9:01', NOT '9:1'  
  }
  lcd.print(curMinutes);
  if(curAM == true){
    lcd.print("AM");  
  }else{
    lcd.print("PM");  
  }
  lcd.setCursor(0,1);
 //LINE 2:
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
  lcd.print("->");
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

void manageRelayState(){
  if(curHours + 1 > onHours && onAM == curAM){
    digitalWrite(relayPin, LOW);//LIGHT ON
  } else if(curHours + 1 == onHours && curMinutes >= onMinutes && onAM == curAM){
    digitalWrite(relayPin, LOW);//LIGHT ON
  } else if(curHours + 1 < offHours && curAM == offAM){
    digitalWrite(relayPin, LOW);//LIGHT ON
  } else if(curHours + 1 == offHours && curMinutes < offMinutes && curAM == offAM){
    digitalWrite(relayPin, LOW);//LIGHT ON
  }else{
    digitalWrite(relayPin, HIGH);//LIGHT OFF
  }  
  
}

void manageBacklight(){
  int protoSwitchState = digitalRead(protoSwitchPin);
  if(previousProtoSwitchState != protoSwitchState && protoSwitchState == 0){
    if(backlight == true){
      lcd.setBacklight(LOW);
      backlight = false;
    }else if (backlight == false){
      lcd.setBacklight(HIGH);
      backlight = true;
    }    
  }
  previousProtoSwitchState = protoSwitchState;
}






