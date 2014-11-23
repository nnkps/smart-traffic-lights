#include <vector>
#ifndef Job_h
#define Job_h

enum LightColor
{
    RED = 0, //zamiast średników stosuje się przecinki
    YELLOW = 1,
    GREEN = 2
};

struct JobItem{
	JobItem(int lc, int l, int d) : lightColor(lc), light(l), delay(d){

	};
	
	int lightColor;
	int light;
	int delay;
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

