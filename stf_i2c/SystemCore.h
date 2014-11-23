#include "Expander.h"
#include "TrafficLight.h"
#include <vector>

#ifndef SystemCore_h
#define SystemCore_h

class SystemCore{
  public:
    SystemCore(int);
    void registerExpander(Expander*);
    void registerTrafficLight(TrafficLight*);
    
    void nextTick(unsigned long int);
    void updateLights();
    void send();
    bool isDone();
    unsigned long int tick;
    unsigned long int last_tick_update;
    int delay;
  private:
    std::vector<TrafficLight*> traffic_lights;
    std::vector<Expander*> expanders;
};

#endif

