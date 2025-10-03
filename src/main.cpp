#include <Arduino.h>

//Pinbelegung
const byte einschalten = 13;  //Pin 13: Start (Schliesser/NO)
const byte ausschalten = 12;  //Pin 12: Stop (Oeffner/NC)
const byte geschwErhoehen = 11; //Geschw. erhoehen
const byte geschwReduzieren = 10; //Geschw. reduzieren
const byte transistorAnsteurung = 6;  //Ansteuerung des Motors per Transistor (PWM-faehig)

//Variablen
bool motorAn = 0; //FALSE = 0
int motorGeschw = 0;  //PWM-Wert: 0-255
const int startGeschw = 125;  //Startwert
const int schrittGeschw = 25; //Schrittweite

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
  ansteuern();
}

//Funktionsdefinitionen
void ansteuern() {
  //Start: Schliesser/NO
  if(digitalRead(einschalten) == LOW && !motorAn) { //Wenn Taste gedrueckt/geschlossen
    motorAn = 1;  //TRUE sind alle Werte ausser 0
    motorGeschw = startGeschw;
    Serial.println("Motor gestartet");
    delay(200); //Entprellen
  }

  //Stop: Oeffner (NC, fail-safe) --> im industriellen Kontext
  //In der Industrie wuerde man einen Oeffner zum Ausschalten verwenden, da ich momentan nur einen Schliesse habe, muss ich
  //den entsprechenden Pin (hier Pin 12) als Schliesse programmieren
  if (digitalRead(ausschalten) == LOW && motorAn) { //Wenn Taste gedrueckt/geoeffnet oder Leitung defekt. Hier LOW zum schliessen verwenden (s. oben)
    motorAn = 0;
    motorGeschw = 0;
    Serial.println("Motor gesoppt");
    delay(200); //Entprellen
  }

  //Geschwindigkeit aendern, wenn Motor laeuft
  if(motorAn) { //Zahlvergleich weggelassen, hier ist die Bed. if(motorAn) gleichbedeutend zu if(motorAn == TRUE)
    analogWrite(transistorAnsteurung, motorGeschw);

    if(digitalRead(geschwErhoehen) == LOW) {
      motorGeschw = min(255, motorGeschw + schrittGeschw);  //Hier verhindert die min()-Fkt., dass das Tastverhaelnis 
                                                            //bei der PWM von 0 bis 255 ueberlaeuft. Nach dem Motto: 
                                                            //"wenn Wert 255 ueberschreittet werden sollte, nimm einfach 255"
      Serial.print("Geschwindigkeit erhoeht auf ");
      Serial.print((motorGeschw  * 100) / 255);
      Serial.println(" %");
      delay(200); //Entprellen
    }

    if(digitalRead(geschwReduzieren) == LOW) {
      motorGeschw = max (0, motorGeschw - schrittGeschw); //Analog zur Geschw.erhoehung. Hier wird verhindert, dass der Motor mit 
                                                          //negativen Zahlen angesteuert wird
      Serial.print("Geschwindigkeit reduziert auf ");
      Serial.print((motorGeschw  * 100) / 255);
      Serial.println(" %");
      delay(200); //Entprellen
    }
  } else {
    analogWrite(transistorAnsteurung, 0); //Sonst Motor aus
  }
}