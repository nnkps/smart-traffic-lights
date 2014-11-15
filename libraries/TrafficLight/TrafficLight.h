#ifndef TrafficLight_h
#define TrafficLight_h

class TrafficLight {
  public:
    TrafficLight(Expander expander, int red, int yellow, int green);

  private:
    int _green;
    int _yellow;
    int _red;
    Expander _expander;
};

#endif
