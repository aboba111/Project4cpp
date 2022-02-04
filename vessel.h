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
    Vessel(int hp, std::pair<int, int >currentXy, int price, char type, int longes, int speed, bool who,
        std::string nameVessel,
        Warehouse* typeWarehouse);

    //virtual void getDataAirplane(char type) {};//?

    std::string getName();

    void setName(std::string name);

    virtual void refreshHeavy() = 0;
    virtual void refreshLung() = 0;
    void byArmament(std::string type);
    /**
     * @brief using the type determine how to move if x is not equal to speed,speed is x
     * @param type object
     * @param x parameter speed
    */
    void move(char type, int x) override;

    Warehouse* getWarehouse();
    ~Vessel() {
        delete typeWarehouse;
    }
};

