#pragma once
#include<iostream>
class object
{
protected:
	int hp;
	std::pair <int, int> currentXy;
	std::pair <int, int> followXy;
	int price;
	char type;
	int speed;
public:
	object() {};
	object(int hp,
	std::pair <int, int> currentXy,
	std::pair <int, int> followXy,
	int price,
	char type,
	int speed) {
		this->hp = hp;
		this->currentXy = currentXy;
		this->price = price;
		this->type = type;
		this->speed = speed;

	}
	virtual void move(char type) = 0;
	void setType(char type) {
		this->type = type;
	}
	void  setCurrentXy(int x, int y) {
		this->currentXy.first = x;
		this->currentXy.second = y;
	}
	std::pair <int, int> getCurrentXy() {
		return currentXy;
	};
	int getDamage(int x) {
		this->hp -= x;
	}
	int getHp() {
		return hp;
	}
	char getType() {
		return type;
	}


};

