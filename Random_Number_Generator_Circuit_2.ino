/**
 * Modul 242 - Mikroprozessoranwendungen realisieren
 * 
 * LB 2
 * Schaltung 2
 * 
 * Stefan Ulrich
 * IAMB16C
 * 03-07-2019
 * 
 * Diese Schaltung wurde frei erfunden.
 * 
 * Diese Schaltung repräsentiert ein Mathe-Spiel.
 * Das Breadboard ist im Hochformat anzusehen und der Knopf sollte sich unten befinden.
 * Es gibt jeweils zwei Spieler die gegeneinander im Kopfrechnen antreten.
 * Wurde der Knopf gedrückt so wird durch ein wellenartiges aufblinken der LED's den beiden Spielern Zeit gewährt.
 * Als nächstes erscheint eine Zahl (von unten nach oben) beide müssen sich die Zahl merken.
 * Danach folgt ein Operator, entweder leuchten beide grünen LED's auf (+) oder beide roten (-).
 * Dann bekommen beide Spieler wieder Zeit.
 * Es erscheint eine weitere Zahl, die dann zur vorherigen Zahl addiert oder subtrahiert werden soll.
 * Darauffolgend erscheint wieder ein Opertaor und eine Zahl.
 * 
 * 
 */
const int firstLedPin = 8;
const int lastLedPin = 13;
const int BUTTON = 7;

const int showOperatorTime = 1000; // default: 1000
const int showNumberTime = 1000; // default: 1000
const int doNothingTime = 500; // default: 500
const int givenWaitTime = 75; // default: 75

int result = 0;
boolean isPlus = true;
boolean wasInLoop = false;

void setup() {
  Serial.begin(9600);
  for(int currentPin = firstLedPin; currentPin <= lastLedPin; currentPin++) {
    pinMode(currentPin, OUTPUT);
  }
  pinMode(BUTTON,INPUT);
}



void loop()
{
  if (digitalRead(BUTTON) == HIGH) {
    result = 0;

    giveTime();
    result = showRandomNumber();
    giveTime();
    showRandomOperator();
    giveTime();
    showRandomNumber();
    giveTime();
    showRandomOperator();
    giveTime();
    showRandomNumber();
    giveTime();
    giveTime();
    giveTime();
    turnOffLeds();
    Serial.print(" = ");
    Serial.println(result);
    delay(1000);
    showResult();
    turnOffLeds();
  }
}

void showResult() {
  if (result >= 0) {
    showGreen(1000); // showOperatorTime
  } else {
    showRed(1000); // showOperatorTime
    result *= -1; // Negative Zahl positiv machen
  }
  
  while (result > 6) {
    if (!wasInLoop) {
      delay(1000);
    }
    wasInLoop = true;
     for(int currentPin = firstLedPin; currentPin <= lastLedPin; currentPin++) {
        digitalWrite(currentPin, HIGH);
    }
    result -= 6;
    delay(1000); // showNumberTime
    turnOffLeds();
    delay(1000); // doNothingTime
  }
  if (!wasInLoop) {
    delay(1000);
  } else {
    wasInLoop = false;
  }
  for (int currentPin = firstLedPin; currentPin <= (result + firstLedPin) - 1; currentPin++) {
    digitalWrite(currentPin, HIGH);
  }
  delay(1000);
}

void showRandomOperator() {
  int randomNumber = random(0, 2);
  //Serial.println(randomNumber);
  if (randomNumber == 1) {
    isPlus = true;
    showGreen(showOperatorTime);
  } else {
    isPlus = false;
    showRed(showOperatorTime);
  }
  turnOffLeds();
  delay(doNothingTime);

  
  if (randomNumber == 1) {
    Serial.print(" + ");
  } else {
    Serial.print(" - ");
  }
  
}



int showRandomNumber() {
      int randomNumber = random(firstLedPin, lastLedPin + 1);
      for (int currentPin = firstLedPin; currentPin <= randomNumber; currentPin++) {
      digitalWrite(currentPin, HIGH);
    }
    delay(showNumberTime);
          for (int currentPin = firstLedPin; currentPin <= randomNumber; currentPin++) {
      digitalWrite(currentPin, LOW);
    }
    turnOffLeds();
    delay(doNothingTime);
    
    Serial.print((randomNumber - firstLedPin) + 1);
    if (isPlus) {
      result += (randomNumber - firstLedPin) + 1;
    } else {
      result -= (randomNumber - firstLedPin) + 1;
    }
    return (randomNumber - firstLedPin) + 1;
}

void giveTime() {
      for (int i = 0; i < 1; i++) {
      for(int currentPin = firstLedPin; currentPin <= lastLedPin; currentPin++) {
        digitalWrite(currentPin, HIGH);
        delay(givenWaitTime);
      }
      for(int currentPin = firstLedPin; currentPin <= lastLedPin; currentPin++) {
        digitalWrite(currentPin, LOW);
        delay(givenWaitTime);
      }
    }
}

void showGreen(int waitTime) {
      for (int currentPin = lastLedPin - 1; currentPin <= lastLedPin; currentPin++) {
      digitalWrite(currentPin, HIGH);
    }
    delay(waitTime);
    turnOffLeds();
}

void showRed(int waitTime) {
      for (int currentPin = firstLedPin; currentPin <= firstLedPin + 1; currentPin++) {
      digitalWrite(currentPin, HIGH);
    }
    delay(waitTime);
    turnOffLeds();
}

void turnOffLeds() {
      for(int currentPin = firstLedPin; currentPin <= lastLedPin; currentPin++) {
        digitalWrite(currentPin, LOW);
    }
}
