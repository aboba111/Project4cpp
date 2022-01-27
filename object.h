#pragma once

#include<iostream>

class Object {
protected:
    int hp;
    std::pair<int, int> currentXy;
    int price;
    char type;
    int longes;
    int speed;
    bool who;
public:

    //Object() {};

    Object(int hp,
    std::pair <int, int> currentXy,
    int price,
    char type,
    int longes,
    int speed,
    bool who) {
        this->hp=hp;
        this-> currentXy= currentXy;
        this-> price= price;
        this-> type= type;
        this-> longes= longes;
        this-> speed= speed;
        this-> who=who;

    }

    virtual void move(char type,int x) = 0;

    void setType(char type) {
        this->type = type;
    }

    void setSpeed(int x) {
        speed = x;
    }

    void setCurrentXy(int x, int y) {
        this->currentXy.first = x;
        this->currentXy.second = y;
    }

    bool getWho() {
        return who;
    }

    std::pair<int, int> getCurrentXy() {
        return currentXy;
    };

    int getSpeed() {
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
    int getPrice() {
        return price;
    }

    int getLonges() {
        return longes;
    }

  /*  int getAttackHp() {
        return attackHp;
    }*/

    void setWho(bool x) {
        who = x;
    }

};

