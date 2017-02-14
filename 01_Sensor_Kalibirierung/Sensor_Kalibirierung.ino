#include <CapacitiveSensor.h>
/*
Nachdem der Code hochgeladen wurde können die Daten über den Seriellen Plotter ausgelesen werden.

Die Farben lassen sich in der Datei "theme.txt" ändern. 
  Die Datei liegt unter Windows in:   /Program Files (x86)/Arduino/lib/theme/theme.txt
                  unter Mac in:       /Applications/Arduino/Arduino.app/Contents/Java/lib/theme/theme.txt
*/
// Initialisieren der Sensorflächen. Jeweils ein 10 megaohm Widerstand zwischen Pin 2 und 3, 2 und 4, 2 und 5, 2 und 6, 2 und 7
CapacitiveSensor   kapazitiver_sensor1 = CapacitiveSensor(2,3);
CapacitiveSensor   kapazitiver_sensor2 = CapacitiveSensor(2,4);
CapacitiveSensor   kapazitiver_sensor3 = CapacitiveSensor(2,5);
CapacitiveSensor   kapazitiver_sensor4 = CapacitiveSensor(2,6);
CapacitiveSensor   kapazitiver_sensor5 = CapacitiveSensor(2,7);

// Wenn die Auflösung heraufgesetzt wird, wird die Performanz herabgesetzt
int aufloesung = 10000;

void setup() {
  Serial.begin(9600);    
}

void loop() {

    long wert_sensor1 = kapazitiver_sensor1.capacitiveSensor(aufloesung);
    long wert_sensor2 = kapazitiver_sensor2.capacitiveSensor(aufloesung);
    long wert_sensor3 = kapazitiver_sensor3.capacitiveSensor(aufloesung);
    long wert_sensor4 = kapazitiver_sensor4.capacitiveSensor(aufloesung);
    long wert_sensor5 = kapazitiver_sensor5.capacitiveSensor(aufloesung);

// Ausgabe der Sensorwerte angepasst für den Seriellen Plotter
    Serial.print(wert_sensor1); Serial.print(",");
    Serial.print(wert_sensor2); Serial.print(",");
    Serial.print(wert_sensor3); Serial.print(",");
    Serial.print(wert_sensor4); Serial.print(",");
    Serial.println(wert_sensor5);
}
