#include <Expander.h>
#include "TrafficLight.h"
#include <Arduino.h>

TrafficLight::TrafficLight(Expander *expander, int green, int yellow, int red, Job* turn_on_green, Job* turn_on_red) : AbstractLight(), expander(expander), tick(0) {
  this->red = red;
  this->yellow = yellow;
  this->green = green;
  this->turn_on_green = turn_on_green;
  this->turn_on_red= turn_on_red;
}

void TrafficLight::turnOnRed() {
  expander->setSingleOutput(red, true);
}

void TrafficLight::turnOnYellow() {
  expander->setSingleOutput(yellow, true);
}

void TrafficLight::turnOnGreen() {
  expander->setSingleOutput(green, true);
}

void TrafficLight::change(int color, int new_state){
  if (color == 1){
      expander->setSingleOutput(green, new_state);
  }else  if (color == 2){
      expander->setSingleOutput(yellow, new_state);
  }else  if (color == 4){
      expander->setSingleOutput(red, new_state);
  }
}

void TrafficLight::runGreenJob(int delay){
  addJob( this->turn_on_green, delay);
}

void TrafficLight::runRedJob(int delay){
  addJob( this->turn_on_red, delay);
}

bool TrafficLight::isDone(){
 return q.empty();
}

void TrafficLight::addJob(Job* j, int delay){
  int start = tick + delay;
  // if( !q.empty())
  //   start = q.back().delay + delay;
  for( int i = 0; i < j->size(); ++i){
    JobItem item = JobItem( (*j)[i]);
    item.delay += start;
    q.push(item);
    Serial.println( q.back().delay);
  }
}

void TrafficLight::update(int tick){
  this->tick = tick;
  while(!q.empty()){
    JobItem item = q.front();
    if( item.delay <= tick){
      this->change( 1, item.getBit(0));
      this->change( 2, item.getBit(1));
      this->change( 4, item.getBit(2));
      q.pop();
    }
    else
      break;
  }
}
