#pragma once
#include"aircraft_carrier.h"
#include"armed_cruiser.h"
class air_cruiser : public aircraft_carrier, public armed_cruiser{
 private:



public:
	air_cruiser() :aircraft_carrier(), armed_cruiser() {
		warehouse* W = new warehouse;
		this->typeWarehouse = W;
		armament* M = new armament;
			this->mass = M;
			this->hp = 1500;
			this->currentXy = currentXy;
			this->price = 160;
			this->longes = 2;
			this->atackHp = 4000;
			this->speed = 1;
			this->maxAirplane = 3;
			this->countAirplane = 3;
			if (std::rand() % 2) {
				fighter* M = new fighter;
				this->plane = M;
			}
			else {
				stormtrooper* M = new stormtrooper;
				this->plane = M;
			}
			vessel* V = dynamic_cast<vessel*>(this);;
			getAirplane()->setParent(V);
		}

	void refreshAmmunition(std::string type)  {
		aircraft_carrier::refreshAmmunition(type);
		armed_cruiser::refreshAmmunition(type);

	};

	~air_cruiser() {
		delete getWarehouse();
		delete getMass();
		delete getAirplane();
	}
};

