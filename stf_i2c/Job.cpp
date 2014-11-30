#include <vector>
#ifndef Job_h
#define Job_h

struct JobItem{
	JobItem(char lc, char l, char d) : lightColor(lc), light(l), delay(d){
        };
	
	char lightColor;
	char light;
	char delay;
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

