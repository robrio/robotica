#include <MeMCore.h>
#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>


#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
 

int note[] = {
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_G5, NOTE_C5, NOTE_D5,
  NOTE_E5,
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
  NOTE_F5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_D5, NOTE_D5, NOTE_E5,
  NOTE_D5, NOTE_G5
};

int durata[] = {
  8, 8, 4,
  8, 8, 4,
  8, 8, 8, 8,
  2,
  8, 8, 8, 8,
  8, 8, 8, 16, 16,
  8, 8, 8, 8,
  4, 4
};

int note_2[] =  {      NOTE_G4,
  NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_G4,
  NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, NOTE_C5,
  NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_G4,
  NOTE_A4, NOTE_G4, NOTE_F4, NOTE_F4,
  NOTE_E4, NOTE_G4, NOTE_C4, NOTE_E4,
  NOTE_D4, NOTE_F4, NOTE_B3,
  NOTE_C4
                  };

int durata_2[] = {     8,
  8, 8, 4, 4, 4,
  8, 8, 4, 4, 4,
  8, 8, 4, 4, 4,
  8, 8, 4, 2,
  4, 4, 4, 4,
  4, 2, 4,
  1 };

MeDCMotor motore_destra(10);
MeDCMotor motore_sinistra(9);
MeRGBLed led(7,2);
MeBuzzer buzzer;
MeLineFollower sensore_linea(2);
MeUltrasonicSensor sensore_distanza(3);

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
   motore_destra.run(velocita);
   motore_sinistra.run(int(-velocita*angolo));
}
void stop() {
   motore_destra.run(0);
   motore_sinistra.run(0);
}

void setup() {
pinMode(A7, INPUT);
led.fillPixelsBak(0,2,1);
}

void prossimanota(int i) {
    int durata_nota        = 0;
    int num_note          = sizeof(note)/sizeof(int);
    durata_nota = 1000 / durata[i%num_note];
    buzzer.tone(note[i%num_note], durata_nota);
    //delay(durata_nota*1.2);
}

void prossimanota_altra_canzone(int i) {
    int durata_nota        = 0;
    int num_note          = sizeof(note)/sizeof(int);
    durata_nota = 1000 / durata_2[i%num_note];
    buzzer.tone(note_2[i%num_note], durata_nota);
    delay(durata_nota*1.2);
}
void passoinavanti(){
 if(sensore_linea.readSensors() == 3) {
  indietro(80);
    delay(100);
    stop();
} 
if(sensore_linea.readSensors() == 0) {
  avanti(80);
    delay(100);
    stop();
} 
if(sensore_linea.readSensors() == 2) {
  avanti_destra(130,0.2);
    delay(100);
    stop();
} 
if(sensore_linea.readSensors() == 1) {
  avanti_sinistra(130,0.2);
    delay(100);
    stop();
} 
}
int i = 0;
bool esegui = false;
void loop() {
    if(analogRead(A7)<150) {
        esegui = true;
    }
    if(esegui) {

        if(sensore_distanza.distanceCm() > 15) {
            prossimanota(i);
            i = i+1;
            passoinavanti();
        }
        else {
            esegui = false;
        }
        if(i%2 == 0){ 
           led.setColor(2, 0, 0, 0);
            led.setColor(1, 255, 0, 0);
            led.show();} else {  
            led.setColor(1, 0, 0, 0);
            led.setColor(2, 0, 255, 0);
            led.show();
        }
    }
    if(!esegui) {
        prossimanota_altra_canzone(i);
        i = i+1; 
    }
   

}
