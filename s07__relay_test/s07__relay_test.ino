int relayPin = 2;
int switchPin = 4;
void setup() {
  pinMode(relayPin, OUTPUT);
  pinMode(switchPin, INPUT);
  digitalWrite(relayPin, HIGH);

}
void loop() {
  int switchState = digitalRead(switchPin);
  if(switchState == HIGH){//BUTTON IS CLOSED
      digitalWrite(relayPin, HIGH);
  }else{
    digitalWrite(relayPin, LOW);
  }
}
//Dope.
