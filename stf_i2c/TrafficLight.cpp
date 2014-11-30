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
  if (color == 0){
      expander->setSingleOutput(red, new_state);
  }else  if (color == 1){
      expander->setSingleOutput(yellow, new_state);
  }else  if (color == 2){
      expander->setSingleOutput(green, new_state);
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
  if( !q.empty())
    start = q.back().delay + delay;
  Serial.println("xxx");
  Serial.println( start );
  Serial.println(j->size());
  for( int i = 0; i < j->size(); ++i){
    Serial.println(i);
    JobItem item = JobItem( (*j)[i]);
    item.delay += start;
    q.push(item);
  }
  Serial.println( q.back().delay);
}

void TrafficLight::update(int tick){
  this->tick = tick;
  while(!q.empty()){
    JobItem item = q.front();
    Serial.println("Item.delay");
    Serial.println(item.delay);
    Serial.println("Tick");
    Serial.println(tick);
    if( item.delay <= tick){
      this->change( item.lightColor, item.light);
      q.pop();
    }
    else
      break;
  }
}
