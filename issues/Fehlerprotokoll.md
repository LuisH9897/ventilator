# Fehlerprotokoll

Dieses Dokument beschreibt die aktuell bekannten Probleme des Projekts und die gewünschte Funktionsweise.

---

## Problem 1: Motorsteuerung über Start-Taster

- **Ist-Zustand:**  
  Der Motor läuft nur an, solange der Start-Taster gedrückt gehalten wird. Sobald der Taster losgelassen wird, stoppt der Motor sofort.  

- **Soll-Zustand:**  
  Der Start-Taster soll lediglich einmal betätigt werden müssen, damit der Motor startet.  
  Der Motor soll danach eigenständig weiterlaufen, bis er über den Stop-Taster abgeschaltet wird.  

- **Mögliche Lösungen:**  
  1. **Anpassung der Programmierlogik:**  
     Umsetzung einer *Flankenerkennung* (Erkennen der Zustandsänderung des Tasters von HIGH → LOW) in Kombination mit Software-Entprellung. Damit wird ein einmaliger Tastendruck als Signal gespeichert, und der Motor bleibt eingeschaltet, bis explizit der Stop-Taster betätigt wird.  
  2. **Hardware-Erweiterung:**  
     Einsatz eines robusteren Treibers (z. B. MOSFET low-side Schaltung mit Gate-Pull-Down und Elko am Motor oder eines Motor-Treiber-Moduls wie TB6612FNG). Dadurch wird verhindert, dass Stromspitzen des Motors die Versorgung des Mikrocontrollers stören und ungewollte Resets oder Abschaltungen verursachen.

---

## Problem 2: Geschwindigkeitsregelung über Taster

- **Ist-Zustand:**  
  Die Geschwindigkeit wird nur erhöht oder reduziert, solange die jeweiligen Taster gedrückt gehalten werden. Wird der Taster losgelassen, springt die Geschwindigkeit wieder zurück.  

- **Soll-Zustand:**  
  Jeder Tastendruck auf „Geschwindigkeit erhöhen“ oder „Geschwindigkeit reduzieren“ soll den PWM-Wert jeweils um einen festen Schritt verändern.  
  Die geänderte Geschwindigkeit soll solange gehalten werden, bis:  
  - ein erneuter Tastendruck erfolgt (Erhöhung oder Reduktion), oder  
  - der Motor gestoppt wird.  

- **Mögliche Lösungen:**  
  1. **Anpassung der Programmierlogik:**  
     Einführung einer Flankenerkennung mit Debounce auch für die Taster „Erhöhen“ und „Reduzieren“. Dadurch wird jeder Tastendruck nur einmal registriert und die Geschwindigkeit entsprechend dauerhaft angepasst.  
  2. **Hardware-Erweiterung:**  
     Nutzung einer stabilen Motoransteuerung (MOSFET oder Treiber-IC) und sauberer Spannungsversorgung mit Abblockkondensatoren. Dies stellt sicher, dass die eingestellte Geschwindigkeit auch bei Motorstromspitzen zuverlässig gehalten wird.

---

## Zusammenfassung

Die Hauptursache für die beschriebenen Probleme liegt in einer Kombination aus:  
- aktueller Programmierlogik (kein Flankentrigger, sondern Dauerabfrage des Tasters)  
- sowie möglichen Strom- und Entstörungsproblemen durch den Aufbau mit PN2222-Transistor und Versorgung über USB.  

**Empfohlener Weg:**  
1. Kurzfristig: Anpassung der Software (Flankenerkennung + Debounce).  
2. Mittelfristig: Erweiterung der Hardware mit logic-level MOSFET oder Motor-Treiber (z. B. TB6612FNG), separater Motorversorgung, Freilaufdiode und Glättungskondensatoren.
