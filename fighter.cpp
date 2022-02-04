#include "Fighter.h"

Fighter::Fighter(std::pair<int, int >currentXy, char type, bool who, Vessel* parent) : Airplane(hpFighter, currentXy, priceFighter, type, longesFighter, attackHpFighter, speedFighter, who, active, new Armament(maxAmmunitionFighter, currentAmmunitionFighter, pattronHeavyDamageFighter, volumForAttackFighter), parent) {

}
void Fighter::attack(Object* M) {
    if (M->getType() == 'c' || M->getType() == 'C' || M->getType() == 's' || M->getType() == 'S') {
        if (mass->getCurrentAmmunition() < mass->getVolumForAttack())
            return;
        mass->attack();
        M->getDamage(mass->attack());
    }
}