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
  int anfangswert = 150;
  if(digitalRead(einschalten) == LOW) {
    analogWrite(einschalten, 200);
    if(digitalRead(geschwErhoehen) == LOW) {
      analogWrite(einschalten, 2);
    }
  }
}