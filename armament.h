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
public:
    Armament(int maxAmmunition, int currentAmmunition, int pattronDamage, int volumForAttack);
    int getVolumForAttack();
    int getMaxAmmunition();
    int getCurrentAmmunition();
    int addPattron(int patrons);
    int attack();
    std::string getNameWeapon();

};

