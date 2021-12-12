#include <MeMCore.h>
#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

MeDCMotor motore_destra(10);
MeDCMotor motore_sinistra(9);
//aggiunto sensore di distanza
MeUltrasonicSensor ultrasonic_3(3);
MeBuzzer buzzer;


void avanti(int velocita) {
   motore_destra.run(velocita);
   motore_sinistra.run(-velocita);
}


void indietro(int velocita) {
   motore_destra.run(-velocita);
   motore_sinistra.run(velocita);
}

void indietro_destra(int velocita, float angolo) {
   motore_destra.run(int(-velocita*angolo));
   motore_sinistra.run(velocita);
}

void avanti_destra(int velocita, float angolo) {
   motore_destra.run(int(velocita*angolo));
   motore_sinistra.run(-velocita);
}

void indietro_sinistra(int velocita, float angolo) {
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
   while(ultrasonic_3.distanceCm()>10) {
   avanti(velocita);
   }
   stop();
   indietro(velocita);
   delay(1000);
   stop();
}

void loop() {

}
