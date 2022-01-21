#pragma once
#include"airplane.h"
class fighter:public airplane
{

public:
	fighter():airplane() {};
	int attack(object*X) override{ 
		if (X->getType() == 'c' || X->getType() == 'C' || X->getType() == 's' || X->getType() == 'S') {
				mass->setCurrentHeavyAmmunition(0);
				return getAtackHp();
			return atackHp;
		}
		else { return 0; }

	}
};

