#include <Expander.h>
#include <TrafficLight.h>

TrafficLight::TrafficLight(Expander &expander, int green, int yellow, int red) : _expander(expander) {
  _red = red;
  _yellow = yellow;
  _green = green;
  this.TurnOnRed()
}

void TrafficLight::TurnOnRed() {
  _expander.setSingleOutput(_red, true);
}

void TrafficLight::TurnOnYellow() {
  _expander.setSingleOutput(_yellow, true);
}

void TrafficLight::TurnOnGreen() {
  _expander.setSingleOutput(_green, true);
}
