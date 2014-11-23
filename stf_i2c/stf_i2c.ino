#include <StandardCplusplus.h>
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <utility.h>

#include <EEPROM.h>
#include <Wire.h>
#include "SystemCore.h"
#include "Expander.h"
#include "TrafficLight.h"
#include "Job.cpp"

using namespace std;

int trigPin = 5;
int echoPin = 6;
byte states[] = {6, 1, 2, 4};
long echoTime;
int mydistance;
int delayTime = 4000;
int sensorPin = A0;
int sensorValue = 0;
int outputPin = 13;
int outputValue = 0;

#define EXPANDERS 2
#define LIGHTS 3

SystemCore core(100);
Expander* expanders[EXPANDERS] = { new Expander(0x20), new Expander(0x21) };

Job* turnOnGreen = new Job();
Job* turnOnRed = new Job();

TrafficLight* l = new TrafficLight(expanders[0], 8, 9, 10, turnOnGreen, turnOnRed);
TrafficLight* p = new TrafficLight(expanders[1], 8, 9, 10, turnOnGreen, turnOnRed);

void setup() {
  Serial.begin(9600);
  // prąd do rezystora
  pinMode(outputPin, OUTPUT);
  // czujnik ruchu
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // ekspander
  Wire.begin(); // rozpoczęcie transmisji
  
  turnOnGreen->registerItem( new JobItem(0, 1, 0));
  turnOnGreen->registerItem( new JobItem(1, 0, 0));
  turnOnGreen->registerItem( new JobItem(2, 0, 0));
  
  turnOnGreen->registerItem( new JobItem(1, 1, 5));
  turnOnGreen->registerItem( new JobItem(0, 0, 10));
  turnOnGreen->registerItem( new JobItem(1, 0, 10));
  turnOnGreen->registerItem( new JobItem(2, 1, 10));
  turnOnGreen->registerItem( new JobItem(2, 1, 20));
  
  
  turnOnRed->registerItem( new JobItem(0, 0, 0));
  turnOnRed->registerItem( new JobItem(1, 0, 0));
  turnOnRed->registerItem( new JobItem(2, 1, 0));
  
  turnOnRed->registerItem( new JobItem(2, 0, 0));
  turnOnRed->registerItem( new JobItem(2, 1, 1));
  turnOnRed->registerItem( new JobItem(2, 0, 2));
  turnOnRed->registerItem( new JobItem(2, 1, 3));
  turnOnRed->registerItem( new JobItem(2, 0, 4));
  turnOnRed->registerItem( new JobItem(2, 1, 5));
  turnOnRed->registerItem( new JobItem(2, 0, 6));
  turnOnRed->registerItem( new JobItem(1, 1, 6));
  turnOnRed->registerItem( new JobItem(0, 1, 11));
  turnOnRed->registerItem( new JobItem(1, 0, 11));
  turnOnRed->registerItem( new JobItem(1, 0, 21));
  
  core.registerExpander(expanders[0]);
  core.registerExpander(expanders[1]);

  core.registerTrafficLight( new TrafficLight(expanders[0], 0, 1, 2, turnOnGreen, turnOnRed));
  core.registerTrafficLight( new TrafficLight(expanders[0], 3, 4, 5, turnOnGreen, turnOnRed));
  core.registerTrafficLight( l);
  core.registerTrafficLight( new TrafficLight(expanders[0], 11, 12, 13, turnOnGreen, turnOnRed));
  core.registerTrafficLight( new TrafficLight(expanders[1], 0, 1, 2, turnOnGreen, turnOnRed));
  core.registerTrafficLight( new TrafficLight(expanders[1], 3, 4, 5, turnOnGreen, turnOnRed));
  core.registerTrafficLight( p);
  core.registerTrafficLight( new TrafficLight(expanders[1], 11, 12, 13, turnOnGreen, turnOnRed));
}

void loop() {
//  Serial.println(millis());
  // czujnik ruchu
//  digitalWrite(trigPin, LOW);
//  delayMicroseconds(2);
//  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(10);
  
//  echoTime = pulseIn(echoPin, HIGH); // odczytanie czasu trwania stanu wysokiego
//  mydistance = echoTime / 58; // obliczenie odległości
//  if(distance <= 200) {
//    for(int i = 0; i < 4; i++) {
//      expander.setOutput(states[i]);
//      delay(delayTime);
//    }  
//  } else {
//    expander.setOutput(4);
//    delay(delayTime);
//  }
  //leftLights.TurnOnGreen();
  //rightLights.TurnOnYellow();
  // fotorezytor
  if( core.isDone() ){
    l->RunGreenJob();
    l->RunRedJob();
    
    p->RunRedJob();
    p->RunGreenJob();
  }
  core.nextTick( millis());
  Serial.println(core.tick);
  
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  outputValue = map(sensorValue, 0, 1023, 10, 255);
  analogWrite(outputPin, outputValue);

  //wait (100 ms - execution time) + dbg
  unsigned long int time = millis();
  Serial.println('W');
  if ( (signed long int)time - (signed long int)core.last_tick_update > 0){
    if ((signed long int)core.delay - (signed long int)( time - core.last_tick_update) > 0){
      Serial.println(core.delay - ( time - core.last_tick_update));
      delay( core.delay - ( time - core.last_tick_update));
    }
    else
      Serial.println('K');
  }
  else
    Serial.println('N');
}
