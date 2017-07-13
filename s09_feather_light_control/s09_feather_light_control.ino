//A 


#include <Adafruit_LiquidCrystal.h>//LCD LIBRARY

Adafruit_LiquidCrystal lcd(0);//CONNECTING TO i2C, DAT PIN #A5 & CLK PIN #A4:

unsigned long previousMillis = 0;

const int relayPin = 5;

//On at 9:00 AM
  const int onHours = 9;
  const int onMinutes = 00;
  const bool onAM = true;
//Off at 10:00 PM 
  const int offHours = 10;
  const int offMinutes = 00;
  const bool offAM = false;

int curHours = 11;
int curMinutes = 00;
int curSeconds = 00;
bool curAM = false;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.setBacklight(HIGH);
  lcd.clear();
  lcd.print("Hello, John");
  delay(2000);
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 1000) {
    previousMillis = currentMillis;
        
    curSeconds = curSeconds + 1;
    printToLCD();//flashes to much on a high refresh rate
  }
  manageTime();
  //manageRelayState();
}


void manageTime(){
  //PROGRESSING MINUTES
  if(curSeconds == 60){
    curSeconds = 0;
    curMinutes = curMinutes + 1;
  }
  //PROGRESSING HOURS
  if(curMinutes == 60){
    curMinutes = 0;
    curHours = curHours + 1;  
  }
  //PROGRESSING AM/PM
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






