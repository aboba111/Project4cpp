#pragma once
#include<iostream>
#include<vector>
#include"vessel.h"
#include"object.h"
class airplane:public object
{
	protected:
	bool active;
	armament * mass;
	vessel* parent;
public:
	airplane() {
		armament* M = new armament;
		this->mass = M;
		this->hp = 100;
		this->currentXy = currentXy;
		this->price = 50;
		this->longes = 1;
		this->atackHp = 20;
		this->speed = 1;
		bool active = false;
	}
	void setParent(vessel* ves) {
		this->parent = ves;
	}
	vessel* getd() {
		return parent;
	}

	virtual int attack(object* X)=0 ;
	armament* getMass() {
		return mass;
	}
	bool setActive(bool active) {
		this->active = active;
	}
	vessel* getParent() {
		return parent;
	}
	int getPrice() {
		return price;
	}
	bool getActive() {
		return active;
	}
	void move(char type) override {
		this->currentXy.first += 1;
	}
	~airplane() {
		delete getMass();
	}
	
};

