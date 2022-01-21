#pragma once
#include<iostream>
class object
{
protected:
	int hp;
	std::pair <int, int> currentXy;
	int price;
	char type;
	int longes;
	int atackHp;
	int speed;
	bool who;
public:
	/*object(int hp,
	std::pair <int, int> currentXy,
	int price,
	char type,
	int longes,
	int atackHp,
	int speed) {
		this->hp=hp;
		this-> currentXy= currentXy;
		this-> price= price;
		this-> type= type;
		this-> longes= longes;
		this-> atackHp= atackHp;
		this-> speed= speed;

	}*/
	virtual void move(char type) = 0;
	void setType(char type) {
		this->type = type;
	}
	void setSpeed(int x) {
		speed = x;
	}
	void  setCurrentXy(int x, int y) {
		this->currentXy.first = x;
		this->currentXy.second = y;
	}
	bool getWho() {
		return who;
	}
	std::pair <int, int> getCurrentXy() {
		return currentXy;
	};
	int getSpeeda() {
		return speed;
	}
	void getDamage(int x) {
		this->hp -= x;
	}
	int getHp() {
		return hp;
	}
	char getType() {
		return type;
	}

	int getLonges() {
		return longes;
	}
	int getAtackHp() {
		return atackHp;
	}

	void setWho(bool x) {
		who = x;
	}

};

