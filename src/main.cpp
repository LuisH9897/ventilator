#include <Arduino.h>

//Pinbelegung
const byte einschalten = 13;  //Pin 13: Start (Schliesser/NO)
const byte ausschalten = 12;  //Pin 12: Stop (Oeffner/NC)
const byte geschwErhoehen = 11; //Geschw. erhoehen
const byte geschwReduzieren = 10; //Geschw. reduzieren
const byte transistorAnsteurung = 6;  //Ansteuerung des Motors per Transistor (PWM-faehig)

//Variablen
bool motorAn = 0;
int motorGeschw = 0;  //PWM-Wert: 0-255
const int startGeschw = 125;  //Startwert
const int schrittGeschw = 10; //Schrittweite

// Funktionsdeklarationen:
void ansteuern();

void setup() {
  pinMode(einschalten, INPUT_PULLUP);
  pinMode(ausschalten, INPUT_PULLUP);
  pinMode(geschwErhoehen, INPUT_PULLUP);
  pinMode(geschwReduzieren, INPUT_PULLUP);
  pinMode(transistorAnsteurung, OUTPUT);

  //Motor stoppen beim Start
  analogWrite(transistorAnsteurung, 0); //Motor aus beim Start
  Serial.begin(9600);
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