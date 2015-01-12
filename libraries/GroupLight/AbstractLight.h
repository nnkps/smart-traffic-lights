#ifndef AbstractLight_h
#define AbstractLight_h

#include "Expander.h"
#include "Job.cpp"

#include <queue>

class AbstractLight {
  public:
    AbstractLight(){};
    virtual void turnOnRed() = 0;
    virtual void turnOnYellow() = 0;
    virtual void turnOnGreen() = 0;
    
    virtual void runRedJob(int delay = 0) = 0;
    virtual void runGreenJob(int delay = 0) = 0;
    virtual void update(int tick) = 0;
    virtual bool isDone() = 0;
    virtual void addJob(Job*, int delay = 0) = 0;
};

#endif
