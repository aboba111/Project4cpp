#pragma once

#include "Airplane.h"
#include "Parametres.h"

class Fighter : public Airplane {

public:

    Fighter( std::pair<int, int >currentXy ,char type, bool who,Vessel* parent) : Airplane(hpFighter,currentXy,priceFighter,type,longesFighter,attackHpFighter,speedFighter,who,active,new Armament(maxAmmunitionFighter, currentAmmunitionFighter,pattronPrice, pattronHeavyDamageFighter, volumForAttackFighter),parent) {

    }

    void attack(Object *M) override {
        if (M->getType() == 'c' || M->getType() == 'C' || M->getType() == 's' || M->getType() == 'S') {
            if (mass->getCurrentAmmunition() < mass->getVolumForAttack())
                return;
            mass->attack();
            M->getDamage(mass->attack());
        } 
    }

      ~Fighter() {
            delete mass;
    } 
};

