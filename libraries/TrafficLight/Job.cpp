#include <vector>
#ifndef Job_h
#define Job_h

struct JobItem{
	JobItem(char state, int d) : state(state), delay(d){
        };
	
	char state;
	int delay;

        char getBit(char pos){
          char a = 1;
          a <<= pos;
          a &= state;
          a >>= pos;
          return a;
        };
};

struct Job{

	void registerItem(JobItem* ji){
		items.push_back(ji);
	};

        int size(){
          return items.size();
        }
        
        JobItem operator[](int pos){
          return *items[pos];
        }
        
	std::vector<JobItem*> items;
};

#endif

