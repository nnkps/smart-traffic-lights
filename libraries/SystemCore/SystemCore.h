#include "Expander.h"
#include "TrafficLight.h"
#include "AbstractLight.h"
#include <Arduino.h>
#include <vector>

#ifndef SystemCore_h
#define SystemCore_h

class SystemCore{
  public:
    SystemCore(int, int, int);
    Expander* registerExpander(Expander*);
    AbstractLight* registerTrafficLight(AbstractLight*);
    
    void nextTick();
    void delayUntilNextTick();
    bool isDone();
    std::vector<AbstractLight*> traffic_lights;
    unsigned long int tick;
    unsigned long int last_tick_update;
    int delta;
  private:
    int sensorPin, outputPin;
    void updateLEDPower();
    void updateLights();
    void send();

    std::vector<Expander*> expanders;
};

#endif

