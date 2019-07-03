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

void setup() {
  for(int currentPin = firstLedPin; currentPin <= lastLedPin; currentPin++) {
    pinMode(currentPin, OUTPUT);
  }
  pinMode(BUTTON,INPUT);
}



void loop()
{
  if (digitalRead(BUTTON) == HIGH) {

    giveTime();
    showRandomNumber();
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
  }

}

void showRandomOperator() {
  int randomNumber = random(1, 3);
  if (randomNumber == 1) {
    for (int currentPin = lastLedPin - 1; currentPin <= lastLedPin; currentPin++) {
      digitalWrite(currentPin, HIGH);
    }
  } else {
    for (int currentPin = firstLedPin; currentPin <= firstLedPin + 1; currentPin++) {
      digitalWrite(currentPin, HIGH);
    }
  }
  delay(1000);
  turnOffLeds();
  delay(500);
}

void showRandomNumber() {
      int randomNumber = random(firstLedPin, lastLedPin + 1);
      for (int currentPin = firstLedPin; currentPin <= randomNumber; currentPin++) {
      digitalWrite(currentPin, HIGH);
    }
    delay(1000);
          for (int currentPin = firstLedPin; currentPin <= randomNumber; currentPin++) {
      digitalWrite(currentPin, LOW);
    }
    turnOffLeds();
    delay(500);
}

void giveTime() {
      for (int i = 0; i < 1; i++) {
      for(int currentPin = firstLedPin; currentPin <= lastLedPin; currentPin++) {
        digitalWrite(currentPin, HIGH);
        delay(75);
      }
      for(int currentPin = firstLedPin; currentPin <= lastLedPin; currentPin++) {
        digitalWrite(currentPin, LOW);
        delay(75);
      }
    }
}

void turnOffLeds() {
      for(int currentPin = firstLedPin; currentPin <= lastLedPin; currentPin++) {
        digitalWrite(currentPin, LOW);
    }
}
