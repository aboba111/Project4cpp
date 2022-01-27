#pragma once

#include <iostream>
#include <vector>
#include "Vessel.h"
#include "Object.h"

class Airplane : public Object {
protected:
    bool active;
    Armament *mass;
    Vessel *parent;
    int attackHp;

public:

    Airplane(int hp, std::pair<int, int >currentXy, int price, char type, int longes, int attackHp, int speed, bool who,
    bool active,
    Armament* mass,
    Vessel* parent
    ) : Object(hp,currentXy,price,type,longes,speed,who) {
        this->active = false;
        this->mass = mass;
        this->parent = parent;
        this->attackHp = attackHp;
    }

    bool getActive() const {
        return active;
    }

    virtual void attack(Object *X) = 0;

    Armament *getMass() {
        return mass;
    }

    void setActive(bool active) {
        this->active = active;
    }

    Vessel *getParent() {
        return parent;
    }

    void setParent(Vessel *ves) {
        this->parent = ves;
    }

    int getPrice() {
        return price;
    }

    bool getActive() {
        return active;
    }

    int getAttackHp() {
        return attackHp;
    }

    void move(char type,int x) override {
        if (x <= speed) {
            if (type == 'C' || type == 'S') {
                this->currentXy.second -= x;
            }
            else
                this->currentXy.second += x;
        }
        else {
            if (type == 'C' || type == 'S') {
                this->currentXy.second -= speed;
            }
            else
                this->currentXy.second += speed;

        }

    }

    ~Airplane() {
     delete mass;
    }

};

