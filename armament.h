#pragma once
#include<iostream>
class armament
{   protected:
	std::string nameWeapon="Pattrom";
	int  maxAmmunition=1000;
	int currentHeavyAmmunition=1000;
	int currentLungAmmunition=1000;
	int price=20;
public:
	void rechargeHeavy() {
		currentHeavyAmmunition = maxAmmunition;
	}
	void rechargeLung() {
		currentLungAmmunition = maxAmmunition;
	}

	int  getMaxAmmunition() {
		return maxAmmunition;
	}
	void setCurrentHeavyAmmunition(int x) {
		currentHeavyAmmunition=x;
	}
	int getCurrentHeavyAmmunition() {
		return currentHeavyAmmunition;
	}
	void setCurrentLungAmmunition(int x) {
		currentLungAmmunition = x;
	}
	int getCurrentLungAmmunition() {
		return currentLungAmmunition;
	}
	int getPrice() {
		return price;
	};
	std::string getNameWeapon() {
		return nameWeapon;
	};

};

