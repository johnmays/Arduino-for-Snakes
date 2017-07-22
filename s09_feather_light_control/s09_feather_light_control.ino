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
Adafruit_LiquidCrystal lcd(0);//CONNECTING TO i2C, DAT PIN #SDA & CLK PIN #SCL:
#include "RTClib.h"
RTC_DS3231 rtc;
#include <Wire.h>

unsigned long previousMillis = 0;

const int relayPin = 9;
const int protoSwitchPin = 10;
int previousProtoSwitchState = 0;

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

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    //SETS CURRENT TIME IF POWER LOST:
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    /* NOTE: JANUARY 21, 2014 AT 3am WOULD LOOK LIKE:
     * rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
     */
  }
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 1000) {
    previousMillis = currentMillis;
    printToLCD();//FLASHES TOO MUCH ON A HIGHER REFRESH RATE, ( >240 Hz)
  }
  
  //manageRelayState();
  manageBacklight();
}

void printToLCD(){
  DateTime now = rtc.now();
  
 //LINE 1: 
  lcd.clear();
  lcd.print("IT IS ");
  if(now.hour() > 12 && now.hour() != 24){
    //IT IS PM
    lcd.print(now.hour() - 12);
    curAM = false;
  }else if(now.hour() < 12){
    //IT IS AM
    lcd.print(now.hour()); 
    curAM = true; 
  }else if(now.hour() == 12){
    //IT IS PM
    lcd.print(now.hour());
    curAM = false;  
  }else if(now.hour() == 24){
    //IT IS AM
    lcd.print(now.hour() - 24);
    curAM = true;  
  }
  lcd.print(":");
  lcd.print(now.minute());
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
    lcd.print("AM");  
  }else{
    lcd.print("PM");  
  }
  lcd.print("->");
  lcd.print(offHours - 12);
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






