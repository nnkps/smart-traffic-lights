#include "SystemCore.h"

SystemCore::SystemCore(int d): traffic_lights(), expanders(), tick(0), last_tick_update(0), delay(d){
	
}

void SystemCore::registerExpander(Expander* e){
  this->expanders.push_back(e);
  e->init();
}

void SystemCore::registerTrafficLight(TrafficLight* tl){
  this->traffic_lights.push_back(tl);
  tl->TurnOnRed();
}

bool SystemCore::isDone(){
  for( int i = 0; i < this->traffic_lights.size(); ++i){
    if( !this->traffic_lights[i]->q.empty())
      return false;
  }
  return true;  
}

void SystemCore::nextTick(unsigned long int milis){
  if (last_tick_update + this->delay <= milis){
   last_tick_update = milis;
   ++tick;
   this->updateLights();
   this->send();
  } 
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
