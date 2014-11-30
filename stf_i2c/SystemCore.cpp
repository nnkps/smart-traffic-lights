#include "SystemCore.h"

SystemCore::SystemCore(int d, int sensorPin, int outputPin): traffic_lights(), expanders(), tick(0), last_tick_update(0), delta(d) {
  this->sensorPin = sensorPin;
  this->outputPin = outputPin;
}

Expander* SystemCore::registerExpander(Expander* e){
  this->expanders.push_back(e);
  e->init();
  return e;
}

AbstractLight* SystemCore::registerTrafficLight(AbstractLight* tl){
  this->traffic_lights.push_back(tl);
  tl->turnOnRed();
  return tl;
}

bool SystemCore::isDone(){
  for( int i = 0; i < this->traffic_lights.size(); ++i){
    if( !this->traffic_lights[i]->isDone())
      return false;
  }
  return true;  
}

void SystemCore::nextTick(){
  unsigned long int milis = millis();
  if (last_tick_update + this->delta <= milis){
   last_tick_update = milis;
   ++tick;
   this->updateLEDPower();
   this->updateLights();
   this->send();
  } 
}

void SystemCore::delayUntilNextTick(){
  unsigned long int time = millis();
  if ( (signed long int)time - (signed long int)this->last_tick_update > 0)
    if ((signed long int)this->delta - (signed long int)( time - this->last_tick_update) > 0){
      //Serial.println(core.delay - ( time - core.last_tick_update));
      delay( this->delta - ( time - this->last_tick_update));
    }
}

void SystemCore::updateLEDPower(){
  int sensorValue = analogRead(sensorPin);
  //Serial.println(sensorValue);
  int outputValue = map(sensorValue, 0, 1023, 10, 255);
  analogWrite(outputPin, outputValue);
}

void SystemCore::updateLights(){
  for( int i = 0; i < this->traffic_lights.size(); ++i){
    this->traffic_lights[i]->update( tick);
  }
}

void SystemCore::send(){
  for( int i =0; i < this->expanders.size(); ++i)
    this->expanders[i]->send();
}
