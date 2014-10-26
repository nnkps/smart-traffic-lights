#include "Wire.h"

int odczyt; 
byte dioda;
int trigPin = 5;
int echoPin = 6;
byte states[] = {6, 1, 2, 4};
long echoTime;
int distance;
int previousDistance = 200;
int delayTime = 4000;

void setup() {
  Serial.begin(9600);
  // czujnik ruchu
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // ekspander
  Wire.begin();
  Wire.beginTransmission(0x20);
  Wire.write((byte)0x01); // init IO port B
  Wire.write((byte)0x00); // ustawienie na output
  Wire.endTransmission();
}

void loop() {
  // pobranie natezenia swiatla z fotorezystora
//  odczyt = analogRead(A0); 
//  odczyt = odczyt/4;
//  if (odczyt < 20) odczyt = 20;
  // czujnik ruchu
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  
  echoTime = pulseIn(echoPin, HIGH); // odczytanie czasu trwania stanu wysokiego
  distance = echoTime / 58; // obliczenie odległości
  if(distance <= 10) {
    for(int i = 0; i < 4; i++) {
      Wire.beginTransmission(0x20);
      Wire.write(0x13); // IO portu A
      Wire.write(states[i]);
      Serial.println(states[i]);
      Wire.endTransmission();
      delay(delayTime);
    }  
  } else {
    Wire.beginTransmission(0x20);
    Wire.write(0x13);
    Wire.write(4); // czerwone światło
    Wire.endTransmission();
    delay(delayTime);
  }
  previousDistance = distance;
}
