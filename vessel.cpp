#include "Vessel.h"

Vessel::Vessel(int hp, std::pair<int, int >currentXy, int price, char type, int longes, int speed, bool who,
    std::string nameVessel,
    Warehouse* typeWarehouse) : Object(hp, currentXy, price, type, longes, speed, who) {
    this->typeWarehouse = typeWarehouse;
    this->nameVessel = nameVessel;
}

//virtual void getDataAirplane(char type) {};//?

std::string Vessel::getName() {
    return nameVessel;
};

void Vessel::setName(std::string name) {
    this->nameVessel = name;
}
void Vessel::byArmament(std::string type) {
    typeWarehouse->byArmament(type);
}

void Vessel::move(char type, int x) {
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

Warehouse* Vessel::getWarehouse() {
    return typeWarehouse;
}


