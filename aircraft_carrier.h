#pragma once
#include"vessel.h"
#include"airplane.h"
#include<vector>
#include "fighter.h"
#include "stormtrooper.h"
class aircraft_carrier :virtual public vessel

{
protected:
	int maxAirplane;
	int countAirplane;
	airplane* plane;
	

public:
	aircraft_carrier():vessel()  {
		warehouse* W = new warehouse;
		this->typeWarehouse = W;
		this->hp = 1500;
		this->currentXy = currentXy;
		this->price = 160;
		this->longes = 1;
		this->atackHp = 40;
		this->speed = 1;
		this->maxAirplane = 3;
		this->countAirplane = 3;
		if (std::rand() % 2) {
			this->plane = new fighter;
		}
		else {
			this->plane = new stormtrooper;
		}
		vessel* M = dynamic_cast<vessel*>(this);
		this->plane->setParent(nullptr);
	
	} 

	airplane* getAirplane() {
		return plane;
	}

	void setAirplane(airplane* air) {
		plane = air;

	}
	
	void startAirplane(int id) {
		countAirplane = maxAirplane - 1;
	}
	void refreshAmmunition(std::string str) override {
		if (plane->getActive() == false) {
			plane->getMass()->rechargeLung();
			typeWarehouse->recharg(str, plane->getMass()->getMaxAmmunition());
		}
		if (plane->getActive() == false) {
			plane->getMass()->rechargeHeavy();
			typeWarehouse->recharg(str, plane->getMass()->getMaxAmmunition());
		}
	}
	~aircraft_carrier() {
		delete getWarehouse();
		delete getAirplane();
	}
};

