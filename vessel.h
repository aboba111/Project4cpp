#pragma once

#include <iostream>
#include <vector>

#include "Warehouse.h"
#include "Object.h"

class Vessel : public Object {
protected:
    std::string nameVessel;
    Warehouse *typeWarehouse;

public:
    Vessel(int hp, std::pair<int, int >currentXy, int price, char type, int longes,int speed,bool who,
    std::string nameVessel,
    Warehouse* typeWarehouse) : Object(hp,currentXy,price,type,longes,speed,who) {
        this->typeWarehouse = typeWarehouse;
        this->nameVessel = nameVessel;
    }

    //virtual void getDataAirplane(char type) {};//?

    std::string getName() {
        return nameVessel;
    };

    void setName(std::string name) {
        this->nameVessel = name;
    }

    virtual void refreshHeavy() = 0;
    virtual void refreshLung() = 0;

    void move(char type,int x) override {
        if (x <= speed) {
            if (type == 'a' || type == 'b' || type == 'd')
                this->currentXy.second += x;
            if (type == 'A' || type == 'B' || type == 'D')
                this->currentXy.second -= x;
        }
        else {
            if (type == 'a' || type == 'b' || type == 'd')
                this->currentXy.second += speed;
            if (type == 'A' || type == 'B' || type == 'D')
                this->currentXy.second -= speed;
        }
    }

    Warehouse *getWarehouse() {
        return typeWarehouse;
    }
    ~Vessel() {
        delete typeWarehouse;
    }
};

