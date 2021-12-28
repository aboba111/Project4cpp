#pragma once
#include<iostream>
class armament
{   protected:
	std::string nameWeapon;
	std::string typeWeapon;
	std::string nameAmmunition;
	bool active;
	int damage;
	int Range;
	int speed;
	int  maxAmmunition;
	int currentAmmunition;
	int price;
public:
	//virtual void shoot(int x);
	void recharge();

	bool setActive();
	int setDamage();
	int setRange();
	int setSpeed();
	int  setMaxAmmunition();
	int setCurrentAmmunition();
	int setPrice();

	int getDamage();
	int getRange();
	int getSpeed();
	int  getMaxAmmunition();
	int getCurrentAmmunition();
	int getPrice();
};

