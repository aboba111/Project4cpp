#pragma once
#include"vessel.h"
#include"airplane.h"
#include<vector>
#include "fighter.h"
#include "stormtrooper.h"
class aircraft_carrier :public vessel

{
protected:
	int maxAirplane;
	int countAirplane;
	std::vector <fighter*> fighterAirplane;
	std::vector <stormtrooper*> stormtrooperAirplane;

public:
	aircraft_carrier() :vessel() {} /* : vessel(nameVessel,
		userName,
		type,
		longs,
		hp,
		currentXy,
		followXy,
		price,
		typeWarehouse)*/ 
	std::vector <fighter*> getFighterAirplane() {
		return fighterAirplane;
	}
	std::vector <stormtrooper*> getStormtrooperAirplane() {
		return stormtrooperAirplane;
	}
	
	

	std::pair<int,int> startAirplane(int id) {
		countAirplane = maxAirplane - 1;
		return currentXy;
	}
	void destructionAirplane(int x);
	void destructionBomber(int x);
	void refreshAmmunition(int id) override {
		//dataAirplane[id]->setPattron(this->dataAirplane[id]->getPattron());
	}
	void getDamage() {
	}
};

