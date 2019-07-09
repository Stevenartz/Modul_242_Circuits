/**
  * Modul 242 - Mikroprozessoranwendungen realisieren
  *
  * LB 2
  * Schaltung 1
  *
  * Stefan Ulrich
  * IAMB16C
  * 29-06-2019
  *
  * Diese Schaltung wurde von einem Beispiel übernommen.
  *
  * Diese Schaltung repräsentiert einen Timer.
  *  
  * Die Schaltung verfügt über ein Display, wo die Zeit wird.
  * Durch das drücken am Knopf oben rechts wird das Programm neu gestartet, es handelt sich also um einen Reset-Knopf.
  * Wird der Knopf unten rechts kurz oder lange gedrückt, so zählt der Timer um 10 Sekunden hoch.
  * Bei fünfzig angekommen, springt die Zeit wieder zurück auf 0.
  * Wird der Knopf unten in der Mitte kurz oder lange gedrückt, so zählt der Timer um eine ganze Minute hoch.
  * Bei 60 Minuten angekommen springt dieser ebenfalls wieder auf die Minute 0.
  * Wird der untere Knopf links kurz gedrückt, so startet der Timer, vorausgesetzt dass eine Zeit gesetzt wurde.
  * Durch einen Knight-Rider Licht-Effekt am 'Multifunctional Shield' wird angezeigt, dass der Timer momentan herunter zählt.
  * Während der Timer läuft, können keine Sekunden sowie Minuten hinzugefügt werden.
  * Durch den Timer Start Knopf kann der Timer ebenfalls gestoppt werden.
  * Im stoppenden Zustand können Minuten sowie Sekunden hinzugefügt werden.
  * Um den Timer zurückzusetzen drückt man lange auf den Knopf unten Links.
  * Der Timer wird nur zurückgesetzt, wenn der Timer vorerst angehalten wurde.
  * Um den Timer in jedem Zustand zurückzusetzen drückt man einfach auf den Reset-Knopf oben rechts.
  *
  */

#include <TimerOne.h>
#include <Wire.h>
#include <MultiFuncShield.h>

enum CountDownModeValues {
    COUNTING_STOPPED,
    COUNTING
};
byte countDownMode = COUNTING_STOPPED;
byte tenths = 0;
char seconds = 0;
char minutes = 0;
short blinking = 0;
short velocity = -1;
void setup() {
    // put your setup code here, to run once:
    Timer1.initialize();
    MFS.initialize( & Timer1); // initialize multi-function shield library
    MFS.write(0);

    Serial.begin(9600);
}
void loop() {
    // put your main code here, to run repeatedly:
    byte btn = MFS.getButton();

    switch (countDownMode) {
    case COUNTING_STOPPED:
        if (btn == BUTTON_1_SHORT_RELEASE && (minutes + seconds) > 0) {
            // start the timer
            countDownMode = COUNTING;
        } else if (btn == BUTTON_1_LONG_PRESSED) {
            // reset the timer
            tenths = 0;
            seconds = 0;
            minutes = 0;
            MFS.write(minutes * 100 + seconds);
            
            // reset blinking
            MFS.writeLeds(LED_ALL, OFF);
            MFS.writeLeds(LED_1, ON);
            blinking = 0;
            velocity = -1;
        } else if (btn == BUTTON_2_PRESSED || btn == BUTTON_2_LONG_PRESSED) {
            minutes++;
            if (minutes > 60) {
                minutes = 0;
            }
            MFS.write(minutes * 100 + seconds);
        } else if (btn == BUTTON_3_PRESSED || btn == BUTTON_3_LONG_PRESSED) {
            seconds += 10;
            if (seconds >= 60) {
                seconds = 0;
            }
            MFS.write(minutes * 100 + seconds);
        }
        break;

    case COUNTING:
        if (btn == BUTTON_1_SHORT_RELEASE || btn == BUTTON_1_LONG_RELEASE) {
            // stop the timer
            countDownMode = COUNTING_STOPPED;
        } else {
            // continue counting down
            tenths++;

            if (blinking >= 3 || blinking <= 0) {
                velocity *= -1;
            }

            // Selbst geschriebeer Code
            if (blinking == 0) {
                MFS.writeLeds(LED_ALL, OFF);
                MFS.writeLeds(LED_1, ON);
            } else if (blinking == 1) {
                MFS.writeLeds(LED_ALL, OFF);
                MFS.writeLeds(LED_2, ON);
            } else if (blinking == 2) {
                MFS.writeLeds(LED_ALL, OFF);
                MFS.writeLeds(LED_3, ON);
            } else if (blinking == 3) {
                MFS.writeLeds(LED_ALL, OFF);
                MFS.writeLeds(LED_4, ON);
            }

            blinking += velocity;

            if (tenths == 10) {
                tenths = 0;
                seconds--;

                if (seconds < 0 && minutes > 0) {
                    seconds = 59;
                    minutes--;
                }

                if (minutes == 0 && seconds == 0) {
                    // timer has reached 0, so sound the alarm
                    MFS.beep(1, 50, 3);
                    countDownMode = COUNTING_STOPPED;
                    MFS.write("End");
                    MFS.blinkDisplay(DIGIT_ALL, ON);
                    MFS.writeLeds(LED_ALL, ON);
                    MFS.blinkLeds(LED_ALL, ON);
                    delay(3000);
                    MFS.writeLeds(LED_ALL, OFF);
                }

                MFS.write(minutes * 100 + seconds);
                MFS.blinkDisplay(DIGIT_ALL, OFF);
                MFS.blinkLeds(LED_ALL, OFF);

            }
            delay(100);
        }
        break;
    }
}
