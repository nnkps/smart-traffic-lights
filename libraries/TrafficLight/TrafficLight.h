#ifndef TrafficLight_h
#define TrafficLight_h

#include <Expander.h>

class TrafficLight {
  public:
    TrafficLight(Expander &expander, int green, int yellow, int red);
    void TurnOnRed();
    void TurnOnYellow();
    void TurnOnGreen();
  protected:
    Expander& _expander;
  private:
    int _green;
    int _yellow;
    int _red;
};

#endif
