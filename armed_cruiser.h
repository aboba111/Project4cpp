#pragma once

#include <iostream>
#include <vector>
#include "Vessel.h"
#include "Armament.h"
#include "Parametres.h"
#include "Heavy_Armament.h"
#include "Lung_Armament.h"

class Armed_cruiser : virtual public Vessel {
protected:
    Armament *lung;
    Armament* heavy;
    int attackHp;
    Armed_cruiser(int attackHp,int hp, std::pair<int, int> currentXy, int price, char type, int longes, int speed, bool who, std::string nameVessel) :Vessel(hp, currentXy, price, type, longes, speed, who, nameVessel, new Warehouse) {
        this->heavy = new Heavy_Armament(maxAmmunitionArmed, currentHeavyAmmunitionArmed, pattronPrice, pattronHeavyDamageArmed, volumForAttackArmed);
        this->lung = new Lung_Armament(maxAmmunitionArmed, currentLungAmmunitionArmed, pattronPrice, pattronLungDamageArmed, volumForAttackArmed);
        this->attackHp = attackHp;
    }
public:
    Armed_cruiser(std::pair<int,int>currentXy,char type,bool who,std::string nameVessel) : Vessel(hpArmed,currentXy,priceArmed,type,longesArmed,speedArmed,who,nameVessel,new Warehouse) {
        this->heavy = new Heavy_Armament(maxAmmunitionArmed, currentHeavyAmmunitionArmed, pattronPrice,pattronHeavyDamageArmed, volumForAttackArmed);
        this->lung = new Lung_Armament(maxAmmunitionArmed, currentLungAmmunitionArmed, pattronPrice, pattronLungDamageArmed, volumForAttackArmed);
        this->attackHp = attackHpArmed;

    }

   
    void refreshLung() override {

        typeWarehouse->AddPatronToWarehouse((lung->addPattron(typeWarehouse->getSomePatronLung(lung->getMaxAmmunition()))),"lung");

    }
    void refreshHeavy() override {

        typeWarehouse->AddPatronToWarehouse((heavy->addPattron(typeWarehouse->getSomePatronHeavy(heavy->getMaxAmmunition()))),"heavy");

    }

    void attack(Object* M) {

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
                getLung()->attack();
                M->getDamage(getHeavy()->attack());
            }
        }

    }


    Armament *getLung() {
        return lung;
    }
    Armament* getHeavy() {
        return heavy;
    }

    int getAttackHp() {
        return attackHp;
    }

    ~Armed_cruiser() {
        delete heavy;
        delete lung;
    }


};

