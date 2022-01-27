#pragma once

#include <iostream>
#include "Parametres.h"

class Armament {
protected:
    std::string nameWeapon = "Patron";
    int maxAmmunition;
    int currentAmmunition;
    int volumForAttack;
    int pattronDamage;
    int price;
public:
    Armament(int maxAmmunition,int currentAmmunition,int price,int pattronDamage,int volumForAttack) {
        this->maxAmmunition = maxAmmunition;
        this->currentAmmunition = currentAmmunition;
        this->price = price;
        this->volumForAttack = volumForAttack;
        this->pattronDamage = pattronDamage;

    }
    int getVolumForAttack() {
        return this->volumForAttack;
    }
    int getMaxAmmunition() {
        return maxAmmunition;
    }
    int getCurrentAmmunition() {
        return currentAmmunition;
    }

    int addPattron(int patrons) {

        int res = (patrons / maxAmmunition) * maxAmmunition;
        patrons -= res;
        if ((currentAmmunition + patrons) / maxAmmunition == 1) {
            currentAmmunition = maxAmmunition;
            res+=(currentAmmunition + patrons) % maxAmmunition;
        }
        else {
            currentAmmunition += patrons;
        }
        return res;
    }

    int attack() {
        currentAmmunition -= volumForAttack;
        return volumForAttack*pattronDamage;
    }


    int getPrice() {
        return price;
    };

    std::string getNameWeapon() {
        return nameWeapon;
    };

};

