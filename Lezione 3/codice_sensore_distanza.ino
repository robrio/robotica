
const int triggerPort = 7;
const int echoPort = 6;
const int led = 13;

void setup() {
  pinMode(triggerPort, OUTPUT);
  pinMode(echoPort, INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  Serial.print( "Sensore Ultrasuoni: ");
}

void loop() {
  //porta bassa l'uscita del trigger
  digitalWrite( triggerPort, LOW );
  //invia un impulso di 10microsec su trigger
  digitalWrite( triggerPort, HIGH );
  delayMicroseconds( 10 );
  digitalWrite( triggerPort, LOW );
  long durata = pulseIn( echoPort, HIGH );
  long distanza = 0.034 * durata / 2;
  Serial.print("distanza: ");

  //dopo 38ms è fuori dalla portata del sensore
  if ( durata > 38000 ) {
    Serial.println("Fuori portata   ");
  }
  else {
    Serial.print(distanza);
    Serial.println(" cm     ");
  }
  
  if (distanza < 130) {
    digitalWrite(led, HIGH);
  }
  else {
    digitalWrite(led, LOW);
  }

  delay(1000);
}
