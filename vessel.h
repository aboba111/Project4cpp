#pragma once
#include<iostream>
#include"warehouse.h"
#include"airplane.h"
#include<vector>
#include"object.h"
class vessel:public object {
protected:
	std::string nameVessel;
	warehouse* typeWarehouse;
   

public:
	vessel() :object() {}
	virtual void getDataAirplane(char type) {};
	std::string getName() {
		return nameVessel;
	};
	void setName(std::string Name) {
		this->nameVessel = Name;
	}
	virtual void refreshAmmunition(std::string str) = 0;
	void move(char type) override {
		if(type=='a'||type=='b'||type=='d')
		this->currentXy.second += 1;
		if(type=='A'||type=='B'||type=='D')
	    this->currentXy.second -= 1;
	}
	warehouse* getWarehouse() {
		return typeWarehouse;
	}
};

