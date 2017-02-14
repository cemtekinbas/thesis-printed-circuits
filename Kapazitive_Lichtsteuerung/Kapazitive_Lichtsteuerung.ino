#include <CapacitiveSensor.h>

// Initialisieren der Sensorflächen. Jeweils ein 10 Megaohm Widerstand zwischen Pin 2 und 3, 2 und 4, 2 und 5, 2 und 6, 2 und 7
CapacitiveSensor   kapazitiver_sensor1 = CapacitiveSensor(2, 3);
CapacitiveSensor   kapazitiver_sensor2 = CapacitiveSensor(2, 4);
CapacitiveSensor   kapazitiver_sensor3 = CapacitiveSensor(2, 5);
CapacitiveSensor   kapazitiver_sensor4 = CapacitiveSensor(2, 6);
CapacitiveSensor   kapazitiver_sensor5 = CapacitiveSensor(2, 7);

// Pin mit 10 Kiloohm Vorwiderstand an Base des Transistors
int pwm_lampe = 9;

// Helligkeit wird zu beginn auf 0 gesetzt. Die Variable wird in der Funktion "dimme_bis" verändert.
int aktuelle_helligkeit = 0;

// Der Schwellenwert kann mithilfe des Kalibrierungsprogramms ausgelesen werden. Je niedriger der Wert, desto früher löst der Sensor aus.
int schwellenwert_sensor = 1500;

// Wenn die Auflösung heraufgesetzt wird, wird die Performanz herabgesetzt. 10000 ist bereits ein hoher Wert.
int aufloesung = 10000;

// Heraufsetzten des Werts verlängert die Zeit des Dimmens. Empfohlene Werte: Halogen (0-255) 5ms, LED (1-100) 10ms
int dimmer_wartezeit = 5;

// Differenzwert gibt an wie groß der Unterschied zu den anderen Sensoren sein muss bevor ausgelöst wird.
int differenz = 1000;

void setup() {
  pinMode(pwm_lampe, OUTPUT);
}

void loop() {

  // Auslesen der Sensordaten
  long wert_sensor1 = kapazitiver_sensor1.capacitiveSensor(aufloesung);
  long wert_sensor2 = kapazitiver_sensor2.capacitiveSensor(aufloesung);
  long wert_sensor3 = kapazitiver_sensor3.capacitiveSensor(aufloesung);
  long wert_sensor4 = kapazitiver_sensor4.capacitiveSensor(aufloesung);
  long wert_sensor5 = kapazitiver_sensor5.capacitiveSensor(aufloesung);

  // Wenn der gemessene Wert größer als der angegebene Schwellenwert und größer als die anderen Messwerte plus Differenz ist wird die Funktion dimme_bis() ausgeführt.
  if (wert_sensor1 > schwellenwert_sensor &&
      wert_sensor1 + differenz > wert_sensor2 &&
      wert_sensor1 + differenz > wert_sensor3 &&
      wert_sensor1 + differenz > wert_sensor4 &&
      wert_sensor1 + differenz > wert_sensor5) {

    dimme_bis(0);
  }

  else if (wert_sensor2 > schwellenwert_sensor &&
           wert_sensor2 + differenz > wert_sensor1 &&
           wert_sensor2 + differenz > wert_sensor3 &&
           wert_sensor2 + differenz > wert_sensor4 &&
           wert_sensor2 + differenz > wert_sensor5) {

    dimme_bis(64);
  }

  else  if (wert_sensor3 > schwellenwert_sensor &&
            wert_sensor3 + differenz > wert_sensor1 &&
            wert_sensor3 + differenz > wert_sensor2 &&
            wert_sensor3 + differenz > wert_sensor4 &&
            wert_sensor3 + differenz > wert_sensor5) {

    dimme_bis(128);
  }

  else  if (wert_sensor4 > schwellenwert_sensor &&
            wert_sensor4 + differenz > wert_sensor1 &&
            wert_sensor4 + differenz > wert_sensor2 &&
            wert_sensor4 + differenz > wert_sensor3 &&
            wert_sensor4 + differenz > wert_sensor5) {

    dimme_bis(192);
  }

  else  if (wert_sensor5 > schwellenwert_sensor &&
            wert_sensor5 + differenz > wert_sensor1 &&
            wert_sensor5 + differenz > wert_sensor2 &&
            wert_sensor5 + differenz > wert_sensor3 &&
            wert_sensor5 + differenz > wert_sensor4) {

    dimme_bis(255);
  }

}

/*
   Die Funktion regelt die Helligkeit auf den übergebenen Wert.
*/
void dimme_bis(int neue_helligkeit) {

  // Erster Fall: Übergebene Helligkeit ist kleiner als die aktuelle Helligkeit. Helligkeit wird heruntergedimmt.
  if (aktuelle_helligkeit > neue_helligkeit) {
    for (int i = aktuelle_helligkeit; i >= neue_helligkeit; i--) {
      analogWrite(pwm_lampe, i);
      delay(dimmer_wartezeit);
    }
    // Zweiter Fall: Übergebene Helligkeit ist größer als die aktuelle Helligkeit. Helligkeit wird heraufgedimmt.
  } else if (aktuelle_helligkeit < neue_helligkeit) {
    for (int i = aktuelle_helligkeit; i <= neue_helligkeit; i++) {
      analogWrite(pwm_lampe, i);
      delay(dimmer_wartezeit);
    }
  }
  aktuelle_helligkeit = neue_helligkeit;
}
