#pragma once
#include<iostream>
#include"warehouse.h"
#include"airplane.h"
#include<vector>
#include"object.h"
class vessel:public object {
protected:
	std::string nameVessel;
	std::string userName;
	int longs;
	warehouse* typeWarehouse;
   

public:
	virtual void getDataAirplane(char type) {};
	vessel():object(){};
	vessel(std::string nameVessel,
		std::string userName,
		char type,
		int longs,
		int hp,
		std::pair <int, int> currentXy,
		std::pair <int, int> followXy,
		int price,
		warehouse* typeWarehouse):object( hp,
			currentXy,
			followXy,
			price,
			type,
			speed) {
		this->nameVessel = nameVessel;
		this->userName = userName;
		this->type = type;
		this->longs = longs;
		this->hp = hp;
		this->price = price;
		this->typeWarehouse = typeWarehouse;
	}
	std::string getRank();
	std::string getName();
	std::string getUserName();
	int getSpeed();
	/*std::pair <int, int> getCurrentXy() {
		return currentXy;
	};*/
	std::pair <int, int> getFollowXy();
	void setName(std::string Name) {
		this->nameVessel = Name;
	}
	std::string setRank();
	std::string  setName();
	std::string  setUserName();
	int  setSpeed();
	int  setHp();
		
	std::pair <int, int>  setFollowXy();
	int  setPrice();
	int getSum();
	//void getPoint(std::pair<int, int>);
	void move(std::pair <int , int > XY) {
	};//переместить
	virtual void refreshAmmunition(int x) = 0;
	void move(char type) override {
		if(type=='a'||type=='b')
		this->currentXy.second += 1;
		if(type=='A'||type=='B')
	    this->currentXy.second -= 1;
	}
	//virtual void getDamage() = 0;

};

