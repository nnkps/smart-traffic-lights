#include <Expander.h>
#include <TrafficLight.h>

// TrafficLight::TrafficLight(Expander const &expander, int green, int yellow, int red) {
//   _red = red;
//   _yellow = yellow;
//   _green = green;
// }

void TrafficLight::TurnOnRed() {
  m_expander.setSingleOutput(_red, true);
}

void TrafficLight::TurnOnYellow() {
  m_expander.setSingleOutput(_yellow, true);
}

void TrafficLight::TurnOnGreen() {
  m_expander.setSingleOutput(_green, true);
}
