#pragma once

#include <vector>
#include "Vessel.h"
#include "Airplane.h"
#include "Fighter.h"
#include "Stormtrooper.h"
#include "Parametres.h"
class Aircraft_carrier : virtual public Vessel {
protected:
    Airplane *plane;
    Aircraft_carrier(int hp, std::pair<int, int> currentXy, int price, char type, int longes, int speed, bool who, std::string nameVessel) :Vessel(hp, currentXy, price, type, longes, speed, who, nameVessel, new Warehouse) {
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

public:
    Aircraft_carrier(std::pair<int,int>currentXy,char type,bool who,std::string nameVessel) : Vessel(hpAircraft, currentXy, priceAircraft, type, longesAircraft, speedAircraft, who, nameVessel, new Warehouse){
     
        if (rand() % 2) {
            if(who==true)
            this->plane = new Fighter(currentXy,'C', who, this);
            else
            this->plane = new Fighter(currentXy, 'c', who, this);
        }
        else {
            if (who == true)
            this->plane = new Stormtrooper(currentXy,'S', who, this);
            else
            this->plane = new Stormtrooper(currentXy, 's', who, this);
        }
    }

    Airplane *getAirplane() {
        return plane;
    }

    void setAirplane(Airplane *air) {
        plane = air;

    }

    void refreshLung() override {
        if (plane->getType() == 'c' || plane->getType() == 'C')
            return;
        Armament* lung =plane->getMass();
        if (!plane->getActive()) {
            typeWarehouse->AddPatronToWarehouse((lung->addPattron(typeWarehouse->getSomePatronLung(lung->getMaxAmmunition()))), "lung");
        }
    }
    void refreshHeavy() override {
        if (plane->getType() == 's' || plane->getType() == 'S')
            return;
        Armament* heavy = plane->getMass();
        if (!plane->getActive()) {
            typeWarehouse->AddPatronToWarehouse((heavy->addPattron(typeWarehouse->getSomePatronLung(heavy->getMaxAmmunition()))), "heavy");
        }
    }

    void startAirplane() {
        plane->setActive(true);
    }

    ~Aircraft_carrier() {
        delete plane;
    }
};

