#include <Wire.h>
#include <Expander.h>


int trigPin = 5;
int echoPin = 6;
long echoTime;
int distance;
int delayTime = 4000;
int sensorPin = A0;
int sensorValue = 0;
int outputPin = 13;
int outputValue = 0;
int delayTime2 = 500;

Expander expander(0x20); // ekspander o adresie szesnastkowym 0x20

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

// tymczasowe rozw.
void sequence() {
    expander.setSingleOutput(0, true);
    expander.setSingleOutput(10, true);
    Serial.println('Debug: ');
    for(int i = 0 ; i < 16; i++) {
      if(expander._outputs[i]) {
        Serial.println(i);
      }
    }
    Serial.println(expander.stateA);
    Serial.println(expander.stateB);
    expander.send();
    delay(delayTime2);
    
    expander.setSingleOutput(1, true);
    expander.setSingleOutput(9, true);
    expander.send();
    delay(delayTime2);
    
    expander.setSingleOutput(2, true);
    expander.setSingleOutput(8, true);
    expander.send();
    delay(delayTime2);
    
    expander.setSingleOutput(1, true);
    expander.setSingleOutput(9, true);
    expander.send();
    delay(delayTime2);
}

void loop() {
  // czujnik ruchu
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  
  echoTime = pulseIn(echoPin, HIGH); // odczytanie czasu trwania stanu wysokiego
  distance = echoTime / 58; // obliczenie odległości
  
  // fotorezytor
  sensorValue = analogRead(sensorPin);
//  Serial.println(sensorValue);
  outputValue = map(sensorValue, 0, 1023, 10, 255);
  analogWrite(outputPin, outputValue);
  
  if(distance <= 200) {
    sequence();
      
  } else {
    expander.setSingleOutput(1, true);
    expander.setSingleOutput(10, true);
    expander.clearOutputs();
  }
 
}
