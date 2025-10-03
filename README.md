# Motorsteuerung mit Arduino (ELEGOO UNO R3)

Dieses Projekt zeigt, wie ein **Gleichstrommotor über Taster gesteuert** werden kann.  
Es werden vier Taster genutzt: Start, Stop, Geschwindigkeit erhöhen, Geschwindigkeit reduzieren.  
Die Ansteuerung des Motors erfolgt per **PWM-Signal** über einen Transistor.

---

## ⚙️ Funktionen

- **Start** über Taster (Schließer, NO) → Motor läuft an.
- **Stop** über Taster (Schließer, aktuell verbaut).  
  👉 Besser wäre ein **Öffner (NC)** als Stop-Taster, da dieser im Fehlerfall (Leitung unterbrochen) automatisch abschaltet.
- **Geschwindigkeit erhöhen** → PWM-Wert steigt in Schritten.
- **Geschwindigkeit reduzieren** → PWM-Wert sinkt in Schritten.
- PWM-Werte werden mit `min()` und `max()` abgesichert (0–255).
- Statusmeldungen über die serielle Schnittstelle (9600 Baud).

---

## 🔌 Hardware

- **Arduino UNO R3 (ELEGOO)**
- **DC TOY/Hobby Motor – 130 Size** (Adafruit Product ID: 711)
- **Transistor PN2222**
- **Widerstand 1 kΩ** (Basisvorwiderstand)
- **Freilaufdiode 1N4007** (parallel zum Motor, Schutz vor Induktionsspitzen)
- **4x Mini-Taster (Schließer, NO)**  
  - Start  
  - Stop (als Schließer verbaut, aber NC wäre bevorzugt)  
  - Geschwindigkeit erhöhen  
  - Geschwindigkeit reduzieren
- **Externe Spannungsversorgung für den Motor** (oder Versorgung über USB/PC für kleine Tests)
- **Gemeinsame Masse** (GND Arduino ↔ GND Motorversorgung)
- 1x Breadboard + Kabelset

---

## 📌 Pinbelegung

| Arduino Pin | Funktion                     |
|-------------|------------------------------|
| D13         | Start (Taster, Schließer)    |
| D12         | Stop (Taster, Schließer / besser: Öffner) |
| D11         | Geschwindigkeit erhöhen      |
| D10         | Geschwindigkeit reduzieren   |
| D6 (PWM)    | Motorsteuerung (Transistor)  |

---

## 🖥️ Software

- **Arduino IDE** oder **PlatformIO** (z. B. mit VS Code)  
- Sprache: C++ (Arduino Core)

### Ablauf

1. Beim Drücken des **Starttasters** wird der Motor eingeschaltet und mit einer Startgeschwindigkeit betrieben.
2. Der Motor bleibt eingeschaltet, bis der **Stop-Taster** betätigt wird.
3. Mit den Tastern **Geschwindigkeit erhöhen/reduzieren** lässt sich die Motordrehzahl (PWM-Wert) anpassen.
4. Der **Stop-Taster** setzt die Motorgeschwindigkeit sofort auf 0.  
   (Mit einem Öffner wäre dies auch im Fehlerfall automatisch gegeben.)

---

## 🔧 Schaltungsvarianten

In diesem Projekt sind **zwei Varianten der Schaltung** vorgesehen:

1. **Steuerung über Taster**  
   - 4 Taster (Start, Stop, Geschwindigkeit +/–)  
   - Diese Variante ist im aktuellen Repository umgesetzt und dokumentiert.  

2. **Steuerung über ein Touch-Modul**  
   - Ein kapazitives Touch-Sensor-Modul ersetzt die mechanischen Taster.  
   - Diese Variante wird später ergänzt.  

---

## 🚀 Installation & Nutzung

1. Repository clonen oder `.ino`/`.cpp` öffnen.
2. Arduino IDE oder PlatformIO starten.
3. Board auswählen (**Arduino UNO**).
4. Sketch hochladen.
5. Serielle Konsole auf **9600 Baud** öffnen (für Statusmeldungen).
6. Motorsteuerung über die Taster testen.

---

## ⚠️ Sicherheitshinweis

- Der gezeigte Aufbau ist ein **Lernprojekt**.  
- Bitte beachte, dass Motoren bei falscher Verdrahtung oder ohne Freilaufdiode Schäden am Arduino oder am Transistor verursachen können.  
- Für ein sicheres Verhalten im Fehlerfall sollte der **Stop-Taster als Öffner (NC)** ausgeführt werden. Da in diesem Projekt nur Schließer verfügbar waren, wurde ein Schließer verwendet.  
