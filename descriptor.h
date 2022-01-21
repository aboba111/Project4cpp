#pragma once
#include <iostream>
#include"table.h"
class descriptor
{   protected:
	table game;
	int damage;
	int numMoney;
public:
	void byVessel() {
	};
	void byAirplane();
	void byWeapon();
	void deleteVessel(std::string x);
	void win();
};

