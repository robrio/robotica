#include <MeMCore.h>
#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

MeDCMotor motore_destra(10);
MeDCMotor motore_sinistra(9);

void avanti(int velocita) {
   delay(1000);
   motore_destra.run(velocita);
   motore_sinistra.run(-velocita);
}


void indietro(int velocita) {
   delay(1000);
   motore_destra.run(-velocita);
   motore_sinistra.run(velocita);
}

void indietro_destra(int velocita, float angolo) {
   delay(1000);
   motore_destra.run(int(-velocita*angolo));
   motore_sinistra.run(velocita);
}

void avanti_destra(int velocita, float angolo) {
   delay(1000);
   motore_destra.run(int(velocita*angolo));
   motore_sinistra.run(-velocita);
}

void indietro_sinistra(int velocita, float angolo) {
   delay(1000);
   motore_destra.run(-velocita);
   motore_sinistra.run(int(velocita*angolo));
}

void avanti_sinistra(int velocita, float angolo) {
   delay(1000);
   motore_destra.run(velocita);
   motore_sinistra.run(int(-velocita*angolo));
}
void stop() {
   motore_destra.run(0);
   motore_sinistra.run(0);
}

void setup() {
   int velocita = 100;
   avanti(velocita);
   delay(1000);
   stop();
   delay(1000);
   indietro(velocita);
   delay(1000);
   stop();
   avanti_destra(velocita,0.7);
   delay(1000);
   stop();
   indietro_sinistra(velocita,0.7);
   delay(1000);
   stop();
}

void loop() {

}