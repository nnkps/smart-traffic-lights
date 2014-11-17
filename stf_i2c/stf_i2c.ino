#include <Wire.h>
#include <Expander.h>
#include <TrafficLight.h>

int trigPin = 5;
int echoPin = 6;
byte states[] = {6, 1, 2, 4};
long echoTime;
int distance;
int delayTime = 4000;
int sensorPin = A0;
int sensorValue = 0;
int outputPin = 13;
int outputValue = 0;

Expander expander(0x20); // ekspander o adresie szesnastkowym 0x20
TrafficLight leftLights(expander, 0, 1, 2);
TrafficLight rightLights(expander, 8, 9, 10);

void setup() {
  Serial.begin(9600);
  // prąd do rezystora
  pinMode(outputPin, OUTPUT);
  // czujnik ruchu
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // ekspander
  Wire.begin(); // rozpoczęcie transmisji
  expander.init();
}

void loop() {

  // czujnik ruchu
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  
  echoTime = pulseIn(echoPin, HIGH); // odczytanie czasu trwania stanu wysokiego
  distance = echoTime / 58; // obliczenie odległości
//  if(distance <= 200) {
//    for(int i = 0; i < 4; i++) {
//      expander.setOutput(states[i]);
//      delay(delayTime);
//    }  
//  } else {
//    expander.setOutput(4);
//    delay(delayTime);
//  }
  leftLights.TurnOnRed();
  rightLights.TurnOnYellow();
  // fotorezytor
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  outputValue = map(sensorValue, 0, 1023, 10, 255);
  analogWrite(outputPin, outputValue);
  // zapalenie odpowiednich diód
  expander.send();
  delay(200);
}
