#pragma once
#include<iostream>
#include<vector>
#include"vessel.h"
#include"object.h"
class airplane:public object
{
	protected:
    char type;
	std::string typeAirplane;
	int damage;
	int hp;
	bool active;
	int speed;
	int consumption;
	int volume;
	int speedConsumption;
	int price;
	int maxPattron;
	std::vector<warehouse> mass;
	armament pattron;
	std::pair <int, int> currentXy;
	std::pair <int, int> followXy;
public:
	airplane():object() {};

	std::pair <int, int> getFollowXy();
	char getType() {
		return type;
	}
	int getPattron() {
		return maxPattron;
	}
	void setPattron(int x) {
		//TODO
	}
	virtual void attack()=0 ;
	void getDamaged(int x);
	void refuel();
	std::string getTypeAirplane();
	int getDamage();
	int getHp();
	bool getActive() {
		return active;
	}
	bool setActive(bool active) {
		this->active = active;
	}
	int getSpeed();
	int getConsumption();
	int getVolume();
	int getSpeedConsumption();
	int getPrice(); 
	std::string setTypeAirplane();
	int setDamage();
	int setHp();
	bool setActive();
	int setSpeed();
	int setConsumption();
	int setVolume();
	int setSpeedConsumption();
	int setPrice();
	void move(char type) override {
		this->currentXy.first += 1;
	}
};

