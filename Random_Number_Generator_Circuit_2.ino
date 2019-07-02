const int firstLedPin = 8;
const int lastLedPin = 13;

int BUTTON = 7;

void setup() {
  for(int currentPin = firstLedPin; currentPin <= lastLedPin; currentPin++) {
    pinMode(currentPin, OUTPUT);
  }
  pinMode(BUTTON,INPUT);
}

void loop(){

  Serial.println(digitalRead(BUTTON));

  if(digitalRead(BUTTON) == HIGH) {
      for(int currentPin = firstLedPin; currentPin <= lastLedPin; currentPin++) {
        digitalWrite(currentPin, HIGH);
      } 
  } else {
      for(int currentPin = firstLedPin; currentPin <= lastLedPin; currentPin++) {
        digitalWrite(currentPin, LOW);
    }
  }

}
