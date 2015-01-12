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
byte states[] = {6, 1, 2, 4};
long echoTime;
int mydistance = 0;
int delayTime = 4000;
int sensorPin = A0;
int sensorValue = 0;
int outputPin = 13;
int outputValue = 0;

#define EXPANDERS 2
#define LIGHTS 3

SystemCore core(700, sensorPin, outputPin);

Expander* expanders[EXPANDERS];

Job* turnOnGreen = new Job();
Job* turnOnRed = new Job();

AbstractLight *top_left, *top_middle, *top_right;
AbstractLight *bot_left, *bot_middle, *bot_right;
AbstractLight *left;
AbstractLight *right;

GroupLight *turn_left, *turn_right, *straight, *left_road, *right_road;

void setup() {
  delay(5000);
  Serial.begin(9600);
  // prąd do rezystora
  pinMode(outputPin, OUTPUT);
  // czujnik ruchu
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // ekspander
  Wire.begin(); // rozpoczęcie transmisji
  
  turnOnGreen->registerItem( new JobItem(6, 5));
  turnOnGreen->registerItem( new JobItem(1, 10));
 
  turnOnRed->registerItem( new JobItem(0, 0));
  turnOnRed->registerItem( new JobItem(1, 1));
  turnOnRed->registerItem( new JobItem(0, 2));
  turnOnRed->registerItem( new JobItem(1, 3));
  turnOnRed->registerItem( new JobItem(0, 4));
  turnOnRed->registerItem( new JobItem(1, 5));
  turnOnRed->registerItem( new JobItem(2, 6));
  turnOnRed->registerItem( new JobItem(4, 11));

  expanders[0] = core.registerExpander(new Expander(0x20));
  expanders[1] = core.registerExpander(new Expander(0x21));

  top_left =   core.registerTrafficLight( new TrafficLight(expanders[0], 4, 3, 2, turnOnGreen, turnOnRed));
  right =      core.registerTrafficLight( new TrafficLight(expanders[0], 7, 6, 5, turnOnGreen, turnOnRed)); //
  top_right =  core.registerTrafficLight( new TrafficLight(expanders[0], 8, 9, 10, turnOnGreen, turnOnRed));
  top_middle = core.registerTrafficLight( new TrafficLight(expanders[0], 11, 12, 13, turnOnGreen, turnOnRed));
  bot_middle = core.registerTrafficLight( new TrafficLight(expanders[1], 4, 3, 2, turnOnGreen, turnOnRed));
  bot_right =  core.registerTrafficLight( new TrafficLight(expanders[1], 7, 6, 5, turnOnGreen, turnOnRed));
  left =       core.registerTrafficLight( new TrafficLight(expanders[1], 8, 9, 10, turnOnGreen, turnOnRed)); //
  bot_left =   core.registerTrafficLight( new TrafficLight(expanders[1], 11, 12, 13, turnOnGreen, turnOnRed));
  
  turn_right = new GroupLight();
  turn_right->registerAbstractLight( top_left);
  turn_right->registerAbstractLight( bot_right);
  
  turn_left = new GroupLight();
  turn_left->registerAbstractLight( bot_left);
  turn_left->registerAbstractLight( top_right);
  
  straight = new GroupLight();
  straight->registerAbstractLight( top_middle);
  straight->registerAbstractLight( bot_middle);
  
  left_road = new GroupLight();
  left_road->registerAbstractLight( right );
  
  right_road = new GroupLight();
  right_road->registerAbstractLight( left );

  core.registerTrafficLight( turn_right);
  core.registerTrafficLight( turn_left);
  core.registerTrafficLight( straight);
  core.registerTrafficLight( left_road );
  core.registerTrafficLight( right_road );
}

void loop() {
//  Serial.println(millis());
  // czujnik ruchu
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  
  echoTime = pulseIn(echoPin, HIGH); // odczytanie czasu trwania stanu wysokiego
  mydistance = echoTime / 58; // obliczenie odległości
//  if(mydistance > 0) {
  if( core.isDone()){
    turn_left->runRedJob();
    turn_left->runGreenJob(10);
    turn_right->runGreenJob();
    turn_right->runRedJob(10);
    straight->runRedJob();
    straight->runGreenJob(10);
    left_road->runGreenJob();
    left_road->runRedJob(10);
    right_road->runGreenJob();
    right_road->runRedJob(10);
  }
  core.nextTick();
  core.delayUntilNextTick();
//  }
}
