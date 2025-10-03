#include <Arduino.h>

//Variablenseklarationen/-initialisierungen:
byte einschalten = 13;  //Pin 13 zum Einschalten
byte ausschalten = 12;  //Pin 12 zum Ausschalten
byte geschwErhoehen = 11; //Geschw. erhoehen
byte geschwReduzieren = 10; //Geschw. reduzieren
byte transistorAnsteurung = 6;  //Ansteuerung des Motors per Transistor

// Funktionsdeklarationen:
void ansteuern();

void setup() {
  pinMode(einschalten, INPUT_PULLUP);
  pinMode(ausschalten, INPUT_PULLUP);
  pinMode(geschwErhoehen, INPUT_PULLUP);
  pinMode(geschwReduzieren, INPUT_PULLUP);
  pinMode(transistorAnsteurung, OUTPUT);

  //Motor stoppen beim Start
  analogWrite(einschalten, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
}

//Funktionsdefinitionen
void ansteuern() {
  int anfangswert = 150;  //Anfangswert beim Einschalten des Motors
  if(digitalRead(einschalten) == LOW) {
    analogWrite(einschalten, anfangswert);
    if(digitalRead(geschwErhoehen) == LOW) {
      anfangswert += 10;  //Anfangswert wird um 10 erhoeht und als neuer Wert gespeichert fuer weitere Berechnungen
      analogWrite(einschalten, anfangswert);
    }
    else if (digitalRead(geschwReduzieren) == LOW) {
      anfangswert -= 10;  //Analog zu geschwErhoehen
      analogWrite(einschalten, anfangswert);
    }
  }
  else if (digitalRead(ausschalten) == LOW) {
    analogWrite(einschalten, 0);
  }
}