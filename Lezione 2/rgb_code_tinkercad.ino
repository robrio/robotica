// C++ code
//
void setup()
{
  Serial.begin(9600);
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
}

void loop()
{
	Serial.println(analogRead(0)/200.0);
    analogWrite(3,analogRead(0)/200.0);
    analogWrite(5,analogRead(1)/200.0);
    analogWrite(6,analogRead(2)/200.0);
}