#pragma once
#include"Armament.h"
class Lung_Armament:public Armament
{
public:
    Lung_Armament(int maxAmmunition, int currentAmmunition, int price, int pattronDamage, int volumForAttack):Armament(maxAmmunition, currentAmmunition, price, pattronDamage, volumForAttack) {

    }
};
