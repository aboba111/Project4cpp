#pragma once
#include"vessel.h"
#include "armament.h"
#include<iostream>
#include <vector>

class armed_cruiser:public vessel
{
protected:
	armament* mass;
public:
	armed_cruiser():vessel() {};
	/*armed_cruiser(std::string nameVessel,
		std::string userName,
		char type,
		int longs,
		int hp,
		std::pair <int, int> currentXy, std::pair <int, int> followXy,
		int price,
		warehouse* typeWarehouse,armament* mass) : vessel(nameVessel,
		userName,
		type,
		longs,
		hp,
		currentXy,
		followXy,
		price,
	    typeWarehouse) {
		this->mass = mass;

	}*/
	void shotShip(std::pair<int,int> xy,int x);
	void shotAirplane(std::pair<int, int> xy, int x);
	void recharge();
	void refreshAmmunition(int id) override {};
	//void vessel::refreshAmmunition(int id) override {};

};

