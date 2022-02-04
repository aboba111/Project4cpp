#pragma once
#include"Armament.h"

class Heavy_Armament:public Armament
{public:
    Heavy_Armament(int maxAmmunition,int currentAmmunition, int pattronDamage,int volumForAttack):Armament(maxAmmunition, currentAmmunition, pattronDamage, volumForAttack) {

    }
};

