#pragma once
#include "armament.h"
class warehouse
{   private:
	int maxArmament;
	int maxCapacity;
	int dataArmament;
public:
	int setMaxArmament();
	int setMaxCapacity();
	int setDataArmament();
	int getMaxArmament();
	int getMaxCapacity();
	int getDataArmament();


};

