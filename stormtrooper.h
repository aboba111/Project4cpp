#pragma once
#include"airplane.h"

class stormtrooper:public airplane
{   public:
	stormtrooper() {};
	int attack(object* X) override {
		if (X->getType() == 'A' || X->getType() == 'a' || X->getType() == 'B' || X->getType() == 'b' || X->getType() == 'D' || X->getType() == 'd') {
			mass->setCurrentLungAmmunition(0);
			return getAtackHp();
			return atackHp;
		}
		else { return 0; }

	}
};

