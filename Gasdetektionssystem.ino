// Pin-Zuweisungen und Variablen
const int MQ2 = A0;         // MQ2 Sensor-Pin an Analogpin A0
int gasValue = 0;           // Variable zum Speichern des Gaswertes
const int fanForward = 9;   // Pin für Lüfter vorwärts
const int fanBackward = 8;  // Pin für Lüfter rückwärts

void setup() 
{
  Serial.begin(9600);        // Initialisiert die serielle Kommunikation mit 9600 Baud
  pinMode(MQ2, INPUT);        // Setzt den MQ2-Pin als Eingang
  pinMode(fanForward, OUTPUT);// Setzt den Pin für den Lüfter vorwärts als Ausgang
  pinMode(fanBackward, OUTPUT);// Setzt den Pin für den Lüfter rückwärts als Ausgang
}

void loop() 
{ 
  gasValue = analogRead(MQ2);  // Liest den aktuellen Wert vom MQ2-Sensor
  
  if (gasValue < 15)          // Überprüft, ob der Gaswert unter einem Schwellenwert von 100 liegt
  {
    stopFan();                 // Lüfter anhalten, wenn Gaswert niedrig ist
  }
  else 
  {
    startFanForward();         // Lüfter vorwärts starten, wenn Gaswert hoch ist
  }
  
  Serial.println(gasValue);    // Ausgabe des Gaswerts über die serielle Schnittstelle
}

// Funktion, um den Lüfter zu stoppen
void stopFan()
{
  digitalWrite(fanForward, LOW); 
  digitalWrite(fanBackward, LOW); 
}

// Funktion, um den Lüfter vorwärts zu starten
void startFanForward()
{
  digitalWrite(fanForward, HIGH); 
  digitalWrite(fanBackward, LOW); 
}