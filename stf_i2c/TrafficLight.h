#ifndef TrafficLight_h
#define TrafficLight_h

#include "Expander.h"
#include "Job.cpp"

#include <queue>

class TrafficLight {
  public:
    TrafficLight(Expander* expander, int green, int yellow, int red, Job* turn_on_green, Job* turn_on_red);
    void TurnOnRed();
    void TurnOnYellow();
    void TurnOnGreen();
    
    void RunRedJob();
    void RunGreenJob();
    void update(int tick);
    void change(int, int);
    void AddJob(Job*);
    
    std::queue<JobItem> q;
    Job* turn_on_green;
    Job* turn_on_red;
  protected:
    Expander* _expander;
  private:
    unsigned long int tick;
    int _green;
    int _yellow;
    int _red;


};

#endif
