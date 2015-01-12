#ifndef TrafficLight_h
#define TrafficLight_h

#include "Expander.h"
#include "Job.cpp"
#include "AbstractLight.h"
#include <queue>

class TrafficLight: public AbstractLight {
  public:
    TrafficLight(Expander* expander, int green, int yellow, int red, Job* turn_on_green, Job* turn_on_red);
    void turnOnRed();
    void turnOnYellow();
    void turnOnGreen();
    
    void runRedJob(int = 0);
    void runGreenJob(int = 0);
    bool isDone();
    void update(int tick);
    void addJob(Job*, int = 0);
    
    std::queue<JobItem> q;
    Job* turn_on_green;
    Job* turn_on_red;
  protected:
    Expander* expander;
  private:
    void change(int, int); //used during job items processsing
    int tick;
    int green;
    int yellow;
    int red;
};

#endif
