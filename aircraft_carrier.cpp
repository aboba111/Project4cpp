#include "Aircraft_carrier.h"
#include "Airplane.h"
Aircraft_carrier::Aircraft_carrier(int hp, std::pair<int, int> currentXy, int price, char type, int longes, int speed, bool who, std::string nameVessel) :Vessel(hp, currentXy, price, type, longes, speed, who, nameVessel, new Warehouse(priceHeavyPatron, priceLungPatron)) {
    if (rand() % 2) {
        if (who == true)
            this->plane = new Fighter(currentXy, 'C', who, this);
        else
            this->plane = new Fighter(currentXy, 'c', who, this);
    }
    else {
        if (who == true)
            this->plane = new Stormtrooper(currentXy, 'S', who, this);
        else
            this->plane = new Stormtrooper(currentXy, 's', who, this);
    }
}

Aircraft_carrier::Aircraft_carrier(std::pair<int, int>currentXy, char type, bool who, std::string nameVessel) : Vessel(hpAircraft, currentXy, priceAircraft, type, longesAircraft, speedAircraft, who, nameVessel, new Warehouse(priceHeavyPatron, priceLungPatron)) {

    if (rand() % 2) {
        if (who == true)
            this->plane = new Fighter(currentXy, 'C', who, this);
        else
            this->plane = new Fighter(currentXy, 'c', who, this);
    }
    else {
        if (who == true)
            this->plane = new Stormtrooper(currentXy, 'S', who, this);
        else
            this->plane = new Stormtrooper(currentXy, 's', who, this);
    }
}

Airplane* Aircraft_carrier::getAirplane() {
    return plane;
}

void Aircraft_carrier::setAirplane(Airplane* air) {
    plane = air;
}
void Aircraft_carrier::refreshLung() {
    if (plane == nullptr)
        return;
    if (plane->getType() == 'c' || plane->getType() == 'C')
        return;
    Armament* lung = plane->getMass();
    if (!plane->getActive()) {
        typeWarehouse->AddPatronToWarehouse((lung->addPattron(typeWarehouse->getSomePatronLung(lung->getMaxAmmunition()))), "lung");
    }
}
void Aircraft_carrier::refreshHeavy() {
    if (plane == nullptr)
        return;
    if (plane->getType() == 's' || plane->getType() == 'S')
        return;
    Armament* heavy = plane->getMass();
    if (!plane->getActive()) {
        typeWarehouse->AddPatronToWarehouse((heavy->addPattron(typeWarehouse->getSomePatronLung(heavy->getMaxAmmunition()))), "heavy");
    }
}
void Aircraft_carrier::startAirplane() {
    plane->setActive(true);
}