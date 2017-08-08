
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  int val = digitalRead(2);
  if(val != 0){
    digitalWrite(1, HIGH);  
  }else{
    digitalWrite(1, LOW);
  }
}
