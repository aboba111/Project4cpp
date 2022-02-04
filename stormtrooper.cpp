#include "Stormtrooper.h"

Stormtrooper::Stormtrooper(std::pair<int, int >currentXy, char type, bool who,
    Vessel* parent) : Airplane(hpStormtrooper, currentXy, priceStormtrooper, type, longesStormtrooper, attackHpStormtrooper, speedStormtrooper, who, active, new Armament(maxAmmunitionStormtrooper, currentAmmunitionStormtrooper, pattronLungDamageStormtrooper, volumForAttackStormtrooper), parent) {

}
void Stormtrooper::attack(Object* M) {
    if (M->getType() == 'A' || M->getType() == 'a' || M->getType() == 'B' || M->getType() == 'b' ||
        M->getType() == 'D' || M->getType() == 'd') {
        if (mass->getCurrentAmmunition() < mass->getVolumForAttack())
            return;
        mass->attack();
        M->getDamage(mass->attack());
    }
}
