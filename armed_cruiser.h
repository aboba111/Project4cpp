#pragma once
#include"vessel.h"
#include "armament.h"
#include<iostream>
#include <vector>

class armed_cruiser: virtual public  vessel
{
protected:
	armament* mass;
	std::string typeAttack;
public:
	armed_cruiser():vessel() {
		warehouse* W = new warehouse;
		this->typeWarehouse = W;
		armament* M = new armament;
		this->mass = M;
		this->hp=1000;
		this-> currentXy= currentXy;
		this-> price= 100;
		this-> longes= 2;
		this-> atackHp= 4000;
		this-> speed= 1;

	}


	void refreshAmmunition(std::string type) override {
		mass->rechargeHeavy();
		mass->rechargeLung();
		typeWarehouse->recharg(type, mass->getMaxAmmunition());

	}
	std::string getTypeAttack() {
		return typeAttack;
	}

	armament* getMass(){
		return mass;
	}
	~armed_cruiser() {
		delete getWarehouse();
		delete getMass();
	}


};

