#include <Expander.h>
#include "TrafficLight.h"

TrafficLight::TrafficLight(Expander *expander, int green, int yellow, int red, Job* turn_on_green, Job* turn_on_red) : _expander(expander), tick(0) {
  _red = red;
  _yellow = yellow;
  _green = green;
  this->turn_on_green = turn_on_green;
  this->turn_on_red= turn_on_red;
}

void TrafficLight::TurnOnRed() {
  _expander->setSingleOutput(_red, true);
}

void TrafficLight::TurnOnYellow() {
  _expander->setSingleOutput(_yellow, true);
}

void TrafficLight::TurnOnGreen() {
  _expander->setSingleOutput(_green, true);
}

void TrafficLight::change(int color, int new_state){
  if (color == 0){
      _expander->setSingleOutput(_red, new_state);
  }else  if (color == 1){
      _expander->setSingleOutput(_yellow, new_state);
  }else  if (color == 2){
      _expander->setSingleOutput(_green, new_state);
  }
}

void TrafficLight::RunGreenJob(){
  AddJob(this->turn_on_green);
}

void TrafficLight::RunRedJob(){
  AddJob(this->turn_on_red);
}

void TrafficLight::AddJob(Job* j){
  int start = tick;
  if( !q.empty())
    start = q.back().delay + 1;
  for( int i = 0; i < j->size(); ++i){
    JobItem item = JobItem( (*j)[i]);
    item.delay += start;
    q.push(item);
  }
}

void TrafficLight::update(int tick){
  this->tick = tick;
  while(!q.empty()){
    JobItem item = q.front();
    if( item.delay <= tick){
      this->change( item.lightColor, item.light);
      q.pop();
    }
    else
      break;
  }
}
