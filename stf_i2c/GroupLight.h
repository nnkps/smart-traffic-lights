#ifndef GroupLight_h
#define GroupLight_h

#include "Expander.h"
#include "Job.cpp"
#include "AbstractLight.h"
#include <vector>

class GroupLight: public AbstractLight {
  public:
    GroupLight(): AbstractLight(){};
    
    void turnOnRed(){
      for(int i = 0; i < this->lights.size(); ++i)
        lights[i]->turnOnRed();
    };
    
    void turnOnYellow(){
      for(int i = 0; i < this->lights.size(); ++i)
        lights[i]->turnOnYellow();
    };
    
    void turnOnGreen(){
      for(int i = 0; i < this->lights.size(); ++i)
        lights[i]->turnOnGreen();
    };
    
    void runRedJob(int delay = 0){
      for(int i = 0; i < this->lights.size(); ++i)
        lights[i]->runRedJob( delay);
    };
    
    void runGreenJob(int delay = 0){
      for(int i = 0; i < this->lights.size(); ++i)
        lights[i]->runGreenJob( delay);
    };
    
    bool isDone(){
      for(int i = 0; i < this->lights.size(); ++i)
        if (!lights[i]->isDone())
          return false;
       return true;
    };
    
    void update(int tick){
      for(int i = 0; i < this->lights.size(); ++i){
        lights[i]->update(tick);
      }
    };
    
    void addJob(Job* j, int delay = 0){
      for(int i = 0; i < this->lights.size(); ++i)
        lights[i]->addJob(j, delay);
    };
    void registerAbstractLight(AbstractLight *al){
      this->lights.push_back(al);
    };
      
  
  private:
    std::vector<AbstractLight*> lights;
};

#endif
