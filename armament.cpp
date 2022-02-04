#include "Armament.h"
Armament::Armament(int maxAmmunition, int currentAmmunition, int pattronDamage, int volumForAttack) {
    this->maxAmmunition = maxAmmunition;
    this->currentAmmunition = currentAmmunition;
    this->volumForAttack = volumForAttack;
    this->pattronDamage = pattronDamage;

}
int Armament::getVolumForAttack() {
    return this->volumForAttack;
}
int Armament::getMaxAmmunition() {
    return maxAmmunition;
}
int Armament::getCurrentAmmunition() {
    return currentAmmunition;
}

int Armament::addPattron(int patrons) {

    int res = 0;
    if (currentAmmunition != maxAmmunition) {
        if ((currentAmmunition + patrons) / maxAmmunition == 1) {
            res += (currentAmmunition + patrons) % maxAmmunition;
            currentAmmunition = maxAmmunition;
        }
        else {
            currentAmmunition += patrons;
        }
    }
    else {
        res += patrons;
    }
    return res;
}

int Armament ::attack() {
    currentAmmunition -= volumForAttack;
    return volumForAttack * pattronDamage;
}

std::string Armament::getNameWeapon() {
    return nameWeapon;
};
