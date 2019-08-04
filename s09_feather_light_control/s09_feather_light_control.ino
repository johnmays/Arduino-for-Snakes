/* PROJECT SUMMARY: 
 * A project using the Adafruit Feather, 1x Relay Wing, 1x Precision
 * RTC Wing, and a 16x2 LCD.  The feather operates the relay to keep a 
 * light on and off in between the two times specified.  It displays 
 * those times and the current time on an LCD for any sort of necessary 
 * checkup.
 */
 
/* CIRCUIT SUMMARY:
 * NOTE: Wings and Feather rest on a FeatherWing Tripler, effectively
 * connecting all necessary wires.
 * NOTE: Relay Control Pin is through Feather Pin [9]
 * NOTE: there is a momentary switch wired into Pin [10]
 * LCD [VIn] to Feather [USB]
 * LCD [Gnd] to Feather [Gnd]
 * LCD [DAT] to Feather [SDA]
 * LCD [CLK] to Feather {SCL]
 */


//LCD LIBRARY
  #include <Adafruit_LiquidCrystal.h>
//CONNECTING TO i2C, DAT PIN #SDA & CLK PIN #SCL:
  Adafruit_LiquidCrystal lcd(0); 
//CLOCK LIBRARY
  #include "RTClib.h"
//IDENTIFYING SPECIFIC CLOCK CHIP
  RTC_DS3231 rtc;
//HAS SOMETHING TO DO WITH ENABLING i2c
  #include <Wire.h>


int previousMinute = 0;

const int relayPin = 9;

const int protoSwitchPin = 10;
int previousProtoSwitchState = 0;

int previousRelayState = 0;

bool backlight = true;

//ON AT 9:00 AM
  const int onHours = 9;
  const int onMinutes = 00;
  bool onAM = true;
//OFF AT 10:00 PM 
  const int offHours = 22;
  const int offMinutes = 00;
  bool offAM = false;
//STILL NEED TO DISPLAY A CURRENT AM
  bool curAM;


void setup() {
  
  lcd.begin(16, 2);
  lcd.setBacklight(HIGH);
  backlight = true;
  lcd.clear();
  lcd.print("Hello, John");
  pinMode(relayPin, OUTPUT);
  pinMode(protoSwitchPin, INPUT);

  
  
  Serial.begin(9600);
  delay(3000);




    Serial.println("RTC lost power, the time will be reset");
    //SETS CURRENT TIME BASED OFF TIME OF SKETCH UPLOAD:
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    /* NOTE: JANUARY 21, 2014 AT 3AM WOULD LOOK LIKE:
     * rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
     */

}

void loop() {
  DateTime now = rtc.now();
  if (now.minute() != previousMinute) {
    //FLASHES TOO MUCH ON A HIGHER REFRESH RATE, NOW ONLY FLASHES ONCE A MINUTE
    printToLCD();
  }
  previousMinute = now.minute();
  manageRelayState();
  manageBacklight();
}

void printToLCD(){
  DateTime now = rtc.now();
  lcd.clear();
  
 //LINE 1: 
  lcd.print("IT IS ");
  if(now.hour() > 12 && now.hour() != 24){
    lcd.print(now.hour() - 12);
    curAM = false;
  }else if(now.hour() < 12 && now.hour() != 0){
    lcd.print(now.hour()); 
    curAM = true; 
  }else if(now.hour() == 12){
    lcd.print(now.hour());
    curAM = false;  
  }else if(now.hour() == 0){
    lcd.print("12");
    curAM = true;  
  }
  lcd.print(":");
  if(now.minute() < 10){
    lcd.print("0");
    lcd.print(now.minute());  
  }else{
    lcd.print(now.minute());
  }
  if(curAM == true){
    lcd.print(" AM");  
  }else{
    lcd.print(" PM");  
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
    lcd.print(" AM");  
  }else{
    lcd.print(" PM");  
  }
  lcd.print("-");
  lcd.print(offHours - 12);
  lcd.print(":");
  if(offMinutes < 10){
     lcd.print("0"); 
  }
  
  lcd.print(offMinutes);
  if(offAM == true){
    lcd.print(" AM");  
  }else{
    lcd.print(" PM");  
  }
}


void manageRelayState(){
  DateTime now = rtc.now();
  
  if(now.hour() > onHours && onAM == curAM){
    digitalWrite(relayPin, HIGH);//LIGHT ON
  } else if(now.hour() == onHours && now.minute() >= onMinutes && onAM == curAM){
    digitalWrite(relayPin, HIGH);//LIGHT ON
  } else if(now.hour() < offHours && curAM == offAM){
    digitalWrite(relayPin, HIGH);//LIGHT ON
  } else if(now.hour() == offHours && now.minute() < offMinutes && curAM == offAM){
    digitalWrite(relayPin, HIGH);//LIGHT ON
  }else{
    digitalWrite(relayPin, LOW);//LIGHT OFF
  }

  //Solution for blink at midnight:
  
  if(now.hour() == 0){
    digitalWrite(relayPin, LOW);//LIGHT OFF
  }
  if(now.hour() == 24){
    digitalWrite(relayPin, LOW);//LIGHT OFF
  }
  
}


void manageBacklight(){
  DateTime now = rtc.now();

  //MANAGING VIA SWITCH
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

  
  //MANAGING VIA TIME OF DAY: (OFF ONCE AT NIGHT, ON ONCE IN MORNING)
  int relayState = digitalRead(relayPin);
  if(previousRelayState != relayState){
    if(backlight == true){
      lcd.setBacklight(LOW);
      backlight = false;
    }else if (backlight == false){
      lcd.setBacklight(HIGH);
      backlight = true;
    }  
  }
  
  previousRelayState = relayState;
  
}
