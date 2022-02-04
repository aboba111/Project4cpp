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
    Armed_cruiser(int attackHp, int hp, std::pair<int, int> currentXy, int price, char type, int longes, int speed, bool who, std::string nameVessel);

public:
    Armed_cruiser(std::pair<int, int>currentXy, char type, bool who, std::string nameVessel);

    /**
     * @brief refresh ammunition,takes lung ammo from storage,if few of them take the rest
    */
    void refreshLung() override;
    /**
     * @brief refresh ammunition,takes heavy ammo from storage,if few of them take the rest
    */
    void refreshHeavy() override;
    /**
     * @brief takes an object and checks if it can be attacked,if hp<0 delete is called
     * @param object being attacked
    */
    void attack(Object* M);


    Armament* getLung();
    Armament* getHeavy();

    int getAttackHp();

    ~Armed_cruiser() {
        delete heavy;
        delete lung;
    }


};

