# Gasdetektionssystem 

Dieses Projekt ist ein einfaches Gasdetektionssystem, das einen Lüfter zur Belüftung aktiviert, wenn eine erhöhte Konzentration von brennbaren Gasen oder Rauch in der Umgebungsluft erkannt wird. Es wurde für Bildungszwecke an der HSHL für den Studiengang Intelligent Systems Design entwickelt, um Einsteiger*innen in die Welt der Embedded Systems einzuführen. Das System liest kontinuierlich den Gaswert über den MQ2-Sensor aus und steuert basierend auf den Messergebnissen einen Lüfter.

## Komponenten

- **Arduino Uno**: Mikrocontroller-Board
- **MQ2-Gassensor**: Erkennt brennbare Gase wie LPG, Methan, Butan und Rauch
- **Lüfter**: Wird bei erhöhter Gaskonzentration aktiviert
- **Verbindungskabel**: Zum Anschluss der Komponenten an das Arduino-Board

## Verkabelung

Die Komponenten werden wie folgt mit dem Arduino verbunden:

- **MQ2-Sensor**:
  - Ausgang (Analog) an A0 
  - VCC an 3.3V 
  - GND an GND 
- **Lüfter**:
  - GND an GND
  - VCC an 5V
  - INB an 8
  - INA an 9 

## Codeerklärung

### Setup-Funktion

Die `setup()`-Funktion initialisiert die serielle Kommunikation, konfiguriert die Pins für den MQ2-Sensor und den Lüfter, und stellt sicher, dass der Lüfter zu Beginn ausgeschaltet ist.

```cpp
void setup() 
{
  // Initialisiert die serielle Kommunikation mit einer Baudrate von 9600 bps
  Serial.begin(9600);
  
  // Setzt den MQ2-Sensor-Pin als Eingang
  pinMode(MQ2, INPUT);
  
  // Setzt die Pins für den Lüfter als Ausgänge
  pinMode(fanForward, OUTPUT);
  pinMode(fanBackward, OUTPUT);
  
  // Schaltet den Lüfter initial aus
  digitalWrite(fanForward, LOW);
  digitalWrite(fanBackward, LOW);
}
```

### Hauptprogramm (Loop)

In der `loop()`-Funktion wird kontinuierlich der Gaswert vom MQ2-Sensor ausgelesen. Wenn der Gaswert über einen definierten Schwellenwert steigt, wird der Lüfter aktiviert, um die Luft zu belüften. Andernfalls bleibt der Lüfter ausgeschaltet.

```cpp
void loop() 
{
  // Liest den aktuellen Wert vom MQ2-Sensor
  gasValue = analogRead(MQ2);
  
  // Überprüft, ob der Gaswert über dem Schwellenwert liegt
  if (gasValue < 100) // Schwellenwert für Gaskonzentration
  {
    stopFan();       // Schaltet den Lüfter aus, wenn der Gaswert niedrig ist
  }
  else 
  {
    startFanForward(); // Schaltet den Lüfter ein, wenn der Gaswert hoch ist
  }
  
  // Ausgabe des Gaswerts über die serielle Verbindung
  Serial.println(gasValue);
}
```

### Zusätzliche Funktionen

Es wurden zwei zusätzliche Funktionen implementiert, um die Steuerung des Lüfters zu vereinfachen.

```cpp
// Funktion zum Ausschalten des Lüfters
void stopFan()
{
  digitalWrite(fanForward, LOW); 
  digitalWrite(fanBackward, LOW); 
}

// Funktion zum Einschalten des Lüfters (Vorwärtsbetrieb)
void startFanForward()
{
  digitalWrite(fanForward, HIGH); 
  digitalWrite(fanBackward, LOW); 
}
```

### Konzeption

Dieses Projekt eignet sich hervorragend für den Einstieg in die Arbeit mit Mikrocontrollern und sensorbasierten Systemen, insbesondere in der Luftqualitätsüberwachung. Es kann als Grundlage für komplexere Systeme verwendet werden, die beispielsweise mehrere Sensoren integrieren oder die Steuerung des Lüfters optimieren.

**Wichtiger Hinweis**: Der MQ2-Gassensor benötigt eine Aufwärmzeit von mehreren Minuten, bevor er zuverlässige Messwerte liefern kann. Diese Aufwärmzeit ist entscheidend für genaue Ergebnisse und sollte unbedingt eingehalten werden. Hierfür einfach die Werte im Seriellen Motor beobachten. Sobald die Werte stagnieren, ist der Sensor betriebsbereit. 

**Erweiterungsmöglichkeiten**:
- Anpassung des Schwellenwerts zur Feinjustierung der Lüftersteuerung
- Integration eines Displays zur Echtzeit-Anzeige der Gaskonzentration
- Einbindung eines drahtlosen Moduls (z.B. Wi-Fi oder Bluetooth) zur Überwachung der Gaskonzentration über eine App oder einen Webserver
- Verwendung eines zusätzlichen Alarmsystems (z.B. Buzzer oder LED) zur Warnung bei gefährlichen Gaskonzentrationen
