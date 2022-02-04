#include "Armed_cruiser.h"

Armed_cruiser::Armed_cruiser(int attackHp, int hp, std::pair<int, int> currentXy, int price, char type, int longes, int speed, bool who, std::string nameVessel) :Vessel(hp, currentXy, price, type, longes, speed, who, nameVessel, new Warehouse(priceHeavyPatron, priceLungPatron)) {
    this->heavy = new Heavy_Armament(maxAmmunitionArmed, currentHeavyAmmunitionArmed, pattronHeavyDamageArmed, volumForAttackArmed);
    this->lung = new Lung_Armament(maxAmmunitionArmed, currentLungAmmunitionArmed, pattronLungDamageArmed, volumForAttackArmed);
    this->attackHp = attackHp;
}

Armed_cruiser::Armed_cruiser(std::pair<int, int>currentXy, char type, bool who, std::string nameVessel) : Vessel(hpArmed, currentXy, priceArmed, type, longesArmed, speedArmed, who, nameVessel, new Warehouse(priceHeavyPatron, priceLungPatron)) {
        this->heavy = new Heavy_Armament(maxAmmunitionArmed, currentHeavyAmmunitionArmed, pattronHeavyDamageArmed, volumForAttackArmed);
        this->lung = new Lung_Armament(maxAmmunitionArmed, currentLungAmmunitionArmed, pattronLungDamageArmed, volumForAttackArmed);
        this->attackHp = attackHpArmed;

    }


    void Armed_cruiser::refreshLung() {

        typeWarehouse->AddPatronToWarehouse((lung->addPattron(typeWarehouse->getSomePatronLung(lung->getMaxAmmunition()))), "lung");

    }
    void Armed_cruiser::refreshHeavy()  {

        typeWarehouse->AddPatronToWarehouse((heavy->addPattron(typeWarehouse->getSomePatronHeavy(heavy->getMaxAmmunition()))), "heavy");

    }

    void Armed_cruiser::attack(Object* M) {

        if (M->getType() == 'c' || M->getType() == 'C' || M->getType() == 'S' || M->getType() == 's') {
            if (getLung()->getCurrentAmmunition() < getLung()->getVolumForAttack())
                return;
            else {
                M->getDamage(getLung()->attack());
            }
        }
        else {
            if (getHeavy()->getCurrentAmmunition() < getHeavy()->getVolumForAttack())
                return;
            else {
                M->getDamage(getHeavy()->attack());
            }
        }

    }


    Armament* Armed_cruiser::getLung() {
        return lung;
    }
    Armament* Armed_cruiser::getHeavy() {
        return heavy;
    }

    int Armed_cruiser::getAttackHp() {
        return attackHp;
    }