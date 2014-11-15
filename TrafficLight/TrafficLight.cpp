#include <Expander.h>

TrafficLight::TrafficLight(Expander expander, int red, int yellow, int green) {
  _expander = expander;
  _red = red;
  _yellow = yellow;
  _green = green;
}
