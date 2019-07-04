/**
   Modul 242 - Mikroprozessoranwendungen realisieren

   LB 2
   Schaltung 2

   Stefan Ulrich
   IAMB16C
   03-07-2019

   Diese Schaltung wurde frei erfunden.

   Diese Schaltung repräsentiert ein Mathe-Training.
   Das Breadboard ist im Hochformat anzusehen und der Knopf befindet sich unten.
   Es gibt ein Spieler, der das Kopfrechnen üben darf.
   Wurde der Knopf gedrückt so wird durch ein wellenartiges aufblinken der LED's dem Spieler Zeit gewährt.
   Dies passiert nach jedem Operator oder nach jeder Zahl.
   Als nächstes erscheint eine Zahl (von unten nach oben) die sich der Spieler merken muss.
   Danach folgt ein Operator, entweder leuchten beide grünen LED's auf (+) oder beide roten (-).
   Es erscheint eine weitere Zahl, die dann zur vorherigen Zahl addiert oder subtrahiert werden soll.
   Darauffolgend erscheint wieder ein Opertaor und eine Zahl.


*/
const int firstLedPin = 8;
const int lastLedPin = 13;
const int numberOfLeds = (lastLedPin - firstLedPin) + 1;
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
  for (int currentPin = firstLedPin; currentPin <= lastLedPin; currentPin++) {
    pinMode(currentPin, OUTPUT);
  }
  pinMode(BUTTON, INPUT);
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
    giveTime();
    turnOffLeds();
  }
}

void showResult() {
  if (result >= 0) {
    showGreen(showOperatorTime);
  } else {
    showRed(showOperatorTime);
    result *= -1; // Negative Zahl positiv machen
  }

  while (result > 6) {
    if (!wasInLoop) {
      delay(1000);
    }
    wasInLoop = true;
    showDynamicNumbers(numberOfLeds);
    result -= numberOfLeds;
    delay(showNumberTime);
    turnOffLeds();
    delay(doNothingTime);
  }
  if (!wasInLoop) {
    delay(showNumberTime);
  } else {
    wasInLoop = false;
  }
  showDynamicNumbers(result);
  delay(showNumberTime);
  turnOffLeds();
  delay(doNothingTime);
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
    for (int currentPin = firstLedPin; currentPin <= lastLedPin; currentPin++) {
      digitalWrite(currentPin, HIGH);
      delay(givenWaitTime);
    }
    for (int currentPin = firstLedPin; currentPin <= lastLedPin; currentPin++) {
      digitalWrite(currentPin, LOW);
      delay(givenWaitTime);
    }
  }
}

void showDynamicNumbers(int numberOfLeds) {
  for (int currentPin = firstLedPin; currentPin <= (numberOfLeds + firstLedPin) - 1; currentPin++) {
    digitalWrite(currentPin, HIGH);
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
  for (int currentPin = firstLedPin; currentPin <= lastLedPin; currentPin++) {
    digitalWrite(currentPin, LOW);
  }
}
