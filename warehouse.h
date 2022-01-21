#pragma once
#include "armament.h"
class warehouse
{   private:
	int heavyArmament=1000;
	int lungArmament=1000;

public:
	void recharg(std::string str,int maxPattron) {
		if (str == "heavy") {
			heavyArmament -= maxPattron;
	}
		if (str == "lung") {
			lungArmament -= maxPattron;
		}
	}

	void setCapacity(int x,std::string str){
		if(str=="heavy")
		heavyArmament += x;
		if (str == "lung")
		lungArmament += x;

	}
	int getHeavyCapacity() {
			return heavyArmament;
	}
	int getLungCapacity() {
		return lungArmament;
	}
};

