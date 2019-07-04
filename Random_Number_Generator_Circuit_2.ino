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
  * Diese Schaltung repraesentiert ein Mathe-Training.
  * Das Breadboard ist im Hochformat anzusehen und der Knopf befindet sich unten.
  * Es gibt ein Spieler, der das Kopfrechnen ueben darf.
  * Wurde der Knopf gedrueckt so wird durch ein wellenartiges aufblinken der LED's dem Spieler Zeit gewaehrt.
  * Dies passiert nach jedem Operator oder nach jeder Zahl.
  * Als naechstes erscheint eine Zahl (von unten nach oben) die sich der Spieler merken muss.
  * Danach folgt ein Operator, entweder leuchten beide gruenen LED's auf (+) oder beide roten (-).
  * Es erscheint eine weitere Zahl, die dann zur vorherigen Zahl addiert oder subtrahiert werden soll.
  * Darauffolgend erscheint wieder ein Opertaor und eine Zahl.
  * Der Spieler muss nun so schnell wie moeglich die Rechnung loesen.
  * Der Spieler hat drei wellenartige aufblinkende LED's Zeit.
  * Nun wird das Ergebnis angezeigt.
  * Zuerst wird festgelegt, ob die Zahl sich im positiven oder negativen Bereich befindet.
  * Dies geschieht anhand der gruenen oder roten LED's.
  * Falls das Ergebnis 0 betraegt, so wird nur de Plus Operator angezeigt.
  * Danach wird die Zahl anhand der LED's angezeigt.
  * Falls das Ergebnis hoeher als 6 bzw. tiefer als -6 betraegt, so schalten die LED's kurz ab und es wird eine weitere Zahl angezeigt.
  * Die Zahlen zusammengerechnet ergeben schlussendlich das Ergebnis.
  * Durch eine weiteres wellenartiges aufblinken der LED's wird das Ergebnis bestaetigt und eine weitere Runde kann via Knopfdruch gespielt werden.
  */

// Konstanten, die nicht geaendert werden sollen
const int firstLedPin = 8;
const int lastLedPin = 13;
const int numberOfLeds = (lastLedPin - firstLedPin) + 1;
const int BUTTON = 7;

const int showOperatorTime = 1000; // default: 1000
const int showNumberTime = 1000; // default: 1000
const int doNothingTime = 500; // default: 500
const int givenWaitTime = 75; // default: 75

// Variablen deklarieren und initialisieren
int result = 0;
boolean isPlus = true;
boolean wasInLoop = false;

void setup() {
  // Notwendig fuer den Serial Monitor
  Serial.begin(9600);
  // Alle LED's als output initialisieren
  for (int currentPin = firstLedPin; currentPin <= lastLedPin; currentPin++) {
    pinMode(currentPin, OUTPUT);
  }
  // Knopf als input initialisieren
  pinMode(BUTTON, INPUT);
}

void loop() {
  // Falls Knopf gedrueckt wurde
  if (digitalRead(BUTTON) == HIGH) {
    result = 0;

    // Spiel Ablauf
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
    // Serial.print(" = ");
    // Serial.println(result);
    delay(1000);
    showResult();
    giveTime();
    turnOffLeds();
  }
}

/**
  * Zeigt das Resultat anhand der LED's an.
  */
void showResult() {
  // Ist das Resultat positiv oder negativ?
  if (result >= 0) {
    showGreen(showOperatorTime);
  } else {
    showRed(showOperatorTime);
    // Negative Zahl zu positiver umwandeln
    result *= -1;
  }

  // Solange das Resultat mehr als 6 betraegt, sollen alle LED's fuer die Ausgabe verwendet werden
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

  // Hier werden die restliche Zahlen unter 6 angezeigt
  showDynamicNumbers(result);
  delay(showNumberTime);
  turnOffLeds();
  delay(doNothingTime);
}

/**
  * Zeigt ein zufaelliger Operator an.
  */
void showRandomOperator() {
  int randomNumber = random(0, 2);
  // globalen Operator setzen
  if (randomNumber == 1) {
    isPlus = true;
    showGreen(showOperatorTime);
  } else {
    isPlus = false;
    showRed(showOperatorTime);
  }
  turnOffLeds();
  delay(doNothingTime);

  // if (randomNumber == 1) {
  //   Serial.print(" + ");
  // } else {
  //   Serial.print(" - ");
  // }

}

/**
  * Zeigt eine zufaellige Zahl an.
  * return: Gibt die zuffaelige Zahl zurueck.
  */
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

  // Serial.print((randomNumber - firstLedPin) + 1);

  // Ergebnis berechnen
  if (isPlus) {
    result += (randomNumber - firstLedPin) + 1;
  } else {
    result -= (randomNumber - firstLedPin) + 1;
  }
  return (randomNumber - firstLedPin) + 1;
}

/**
  * Gewaehrt dem Spieler durch wellenartiges Anzeigen der LED's Zeit.
  */
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

/**
  * Zeigt eine bestimmte Zahl anhand der LED's an.
  * param: Die gewuenschte Zahl, die angezeigt werden sollte.
  */
void showDynamicNumbers(int numberOfLeds) {
  for (int currentPin = firstLedPin; currentPin <= (numberOfLeds + firstLedPin) - 1; currentPin++) {
    digitalWrite(currentPin, HIGH);
  }
}

/**
  * Zeigt die gruenen LED's fuer eine bestimmte Zeit an.
  * param: Die gewuenschte Wartezeit.
  */
void showGreen(int waitTime) {
  for (int currentPin = lastLedPin - 1; currentPin <= lastLedPin; currentPin++) {
    digitalWrite(currentPin, HIGH);
  }
  delay(waitTime);
  turnOffLeds();
}

/**
  * Zeigt die roten LED's fuer eine bestimmte Zeit an.
  * param: Die gewuenschte Wartezeit.
  */
void showRed(int waitTime) {
  for (int currentPin = firstLedPin; currentPin <= firstLedPin + 1; currentPin++) {
    digitalWrite(currentPin, HIGH);
  }
  delay(waitTime);
  turnOffLeds();
}

/**
  * Schaltet alle LED's ab.
  */
void turnOffLeds() {
  for (int currentPin = firstLedPin; currentPin <= lastLedPin; currentPin++) {
    digitalWrite(currentPin, LOW);
  }
}
