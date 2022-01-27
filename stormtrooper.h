#pragma once

#include"Airplane.h"
#include "Parametres.h"
class Stormtrooper : public Airplane {
public:

    Stormtrooper(std::pair<int, int >currentXy, char type, bool who,
        Vessel* parent) : Airplane(hpStormtrooper, currentXy, priceStormtrooper, type, longesStormtrooper, attackHpStormtrooper, speedStormtrooper, who, active, new Armament(maxAmmunitionStormtrooper, currentAmmunitionStormtrooper, pattronPrice, pattronLungDamageStormtrooper, volumForAttackStormtrooper), parent) {

}

    void attack(Object *M) override {
        if (M->getType() == 'A' || M->getType() == 'a' || M->getType() == 'B' || M->getType() == 'b' ||
            M->getType() == 'D' || M->getType() == 'd') {
            if (mass->getCurrentAmmunition() < mass->getVolumForAttack())
                return;
            mass->attack();
            M->getDamage(mass->attack());
        }
    }

   ~Stormtrooper(){
        delete mass;
    }
};

