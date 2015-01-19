#include <StandardCplusplus.h>
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <utility.h>

#include <EEPROM.h>
#include <Wire.h>
#include "SystemCore.h"
#include "Expander.h"
#include "TrafficLight.h"
#include "GroupLight.h"
#include "Job.cpp"

using namespace std;

int trigPin = 5;
int echoPin = 6;
long echoTime;
int mydistance = 0;
int delayTime = 4000;
int sensorPin = A0;
int sensorValue = 0;
int outputPin = 13;
int outputValue = 0;
int i = 0;
int current_state = 0;
boolean def = false;

#define EXPANDERS 2
#define LIGHTS 3
#define BUTTONS 3

SystemCore core(700, sensorPin, outputPin);

Expander* expanders[EXPANDERS];
int buttonPins[4] = {8, 9, 10, 0};
int buttonStates[4] = {0, 0, 0, 0};
int echoState = 0;


Job* turnOnGreen = new Job();
Job* turnOnRed = new Job();

AbstractLight *top_left, *top_middle, *top_right;
AbstractLight *bot_left, *bot_middle, *bot_right;
AbstractLight *left;
AbstractLight *right;

GroupLight *group[4];

void setup() {
  delay(5000);
  Serial.begin(9600);
  // buttony
  for(int i = 1; i < 4; i++) {
    pinMode(buttonPins[i], INPUT);
  }
  // prąd do rezystora
  pinMode(outputPin, OUTPUT);
  // czujnik ruchu
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // ekspander
  Wire.begin(); // rozpoczęcie transmisji
  
  // akcje, ktore definiujemy do zmiany na zielone
  turnOnGreen->registerItem( new JobItem(4, 0));
  turnOnGreen->registerItem( new JobItem(6, 4));
  turnOnGreen->registerItem( new JobItem(1, 7));
//  turnOnGreen->registerItem( new JobItem(1, 12));
  // akcje do zmiany na czerwone - miganie zielonego najpierw
  turnOnRed->registerItem( new JobItem(0, 0));
  turnOnRed->registerItem( new JobItem(1, 1));
  turnOnRed->registerItem( new JobItem(0, 2));
  turnOnRed->registerItem( new JobItem(2, 3));
  turnOnRed->registerItem( new JobItem(4, 7));
//  turnOnRed->registerItem( new JobItem(4, 12));

  // ekspandery, na ktore bedziemy transmitowac zapalenie poszczegolnych diod
  expanders[0] = core.registerExpander(new Expander(0x20));
  expanders[1] = core.registerExpander(new Expander(0x21));

  // definiujemy sygnalizacje swietlne
  top_left =   core.registerTrafficLight( new TrafficLight(expanders[0], 4, 3, 2, turnOnGreen, turnOnRed));
  right =      core.registerTrafficLight( new TrafficLight(expanders[0], 7, 6, 5, turnOnGreen, turnOnRed)); //
  top_right =  core.registerTrafficLight( new TrafficLight(expanders[0], 8, 9, 10, turnOnGreen, turnOnRed));
  top_middle = core.registerTrafficLight( new TrafficLight(expanders[0], 11, 12, 13, turnOnGreen, turnOnRed));
  bot_middle = core.registerTrafficLight( new TrafficLight(expanders[1], 4, 3, 2, turnOnGreen, turnOnRed));
  bot_right =  core.registerTrafficLight( new TrafficLight(expanders[1], 7, 6, 5, turnOnGreen, turnOnRed));
  left =       core.registerTrafficLight( new TrafficLight(expanders[1], 8, 9, 10, turnOnGreen, turnOnRed)); //
  bot_left =   core.registerTrafficLight( new TrafficLight(expanders[1], 11, 12, 13, turnOnGreen, turnOnRed));
  
  // definiujemy grupy sygnalizacji, ktore beda swiecic w ten sam sposob
  group[2] = new GroupLight();
  group[2]->registerAbstractLight( bot_left );
  
  group[1] = new GroupLight();
  group[1]->registerAbstractLight( top_right );
  
  group[0] = new GroupLight();
  group[0]->registerAbstractLight( top_middle );
  group[0]->registerAbstractLight( bot_middle );
  group[0]->registerAbstractLight( top_left );
  group[0]->registerAbstractLight( bot_right );
  
  group[3] = new GroupLight();
  group[3]->registerAbstractLight( right );
  group[3]->registerAbstractLight( left );

  core.registerTrafficLight( group[0] );
  core.registerTrafficLight( group[1] );
  core.registerTrafficLight( group[2] );
  core.registerTrafficLight( group[3] );
}

boolean isAnyCar(int buttonStates[], int size){
  for( int i = 0; i < size; ++i)
    if (buttonStates[i]) return true;
  return false;
}

void loop() {
  // czujnik ruchu
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  
  echoTime = pulseIn(echoPin, HIGH); // odczytanie czasu trwania stanu wysokiego
  mydistance = echoTime / 58; // obliczenie odległości
  // odczytanie stanu czujnikow
  echoState = (mydistance <= 10);
  for(int i = 0; i < 3; i++) {
    buttonStates[i] = digitalRead(buttonPins[i]);
  }
  buttonStates[3] = echoState;
  // glowna petla - podstawowe dzialanie bez czujnikow
  if( core.isDone()){
    if( ! isAnyCar( buttonStates, 4)){
      if( !def ){
        group[0]->runGreenJob();
        def = true;
      }
    }
    else{
      int counter = 0;
      for( int i = 0; i < 4; ++i){
        if (buttonStates[i]){
          if(def){
            group[0]->runRedJob();
            def = false;
          }
          group[i]->runGreenJob(12 * counter);
          group[i]->runRedJob(12 + 12 * counter);
          ++counter;        
        }
        
      }
    }
//    if (buttonStates[1]){
//      
//    }
//    group_1->runRedJob(i);
//    group_2->runGreenJob(i);
//    i += 12;
//    group_2->runRedJob(i);
//    group_3->runGreenJob(i);
//    i += 12;
//    group_3->runRedJob(i);
//    group_4->runGreenJob(i);
//    i += 12;
//    group_4->runRedJob(i);
//    group_1->runGreenJob(i);
  }
  core.nextTick();
  core.delayUntilNextTick();
}
