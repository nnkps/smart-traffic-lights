#ifndef TrafficLight_h
#define TrafficLight_h

#include <Expander.h>

class TrafficLight {
  public:
    TrafficLight(Expander const &expander, int green, int yellow, int red) : m_expander(expander) {};
    void TurnOnRed();
    void TurnOnYellow();
    void TurnOnGreen();
  protected:
    const Expander& m_expander;
  private:
    int _green;
    int _yellow;
    int _red;
};

#endif
