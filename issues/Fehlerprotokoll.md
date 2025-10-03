# Fehlerprotokoll

Dieses Dokument beschreibt die aktuell bekannten Probleme des Projekts und die gewünschte Funktionsweise.

---

## Problem 1: Motorsteuerung über Start-Taster

- **Ist-Zustand:**  
  Der Motor läuft nur an, solange der Start-Taster gedrückt gehalten wird. Sobald der Taster losgelassen wird, stoppt der Motor sofort.  

- **Soll-Zustand:**  
  Der Start-Taster soll lediglich einmal betätigt werden müssen, damit der Motor startet.  
  Der Motor soll danach eigenständig weiterlaufen, bis er über den Stop-Taster abgeschaltet wird.  

---

## Problem 2: Geschwindigkeitsregelung über Taster

- **Ist-Zustand:**  
  Die Geschwindigkeit wird nur erhöht oder reduziert, solange die jeweiligen Taster gedrückt gehalten werden. Wird der Taster losgelassen, springt die Geschwindigkeit wieder zurück.  

- **Soll-Zustand:**  
  Jeder Tastendruck auf „Geschwindigkeit erhöhen“ oder „Geschwindigkeit reduzieren“ soll den PWM-Wert jeweils um einen festen Schritt verändern.  
  Die geänderte Geschwindigkeit soll solange gehalten werden, bis:  
  - ein erneuter Tastendruck erfolgt (Erhöhung oder Reduktion), oder  
  - der Motor gestoppt wird.  

---
