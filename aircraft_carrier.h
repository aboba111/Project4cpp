#pragma once

#include <vector>
#include "Vessel.h"
#include "Airplane.h"
#include "Fighter.h"
#include "Stormtrooper.h"
#include "Parametres.h"
class Aircraft_carrier : virtual public Vessel {
protected:
    Airplane *plane;
    Aircraft_carrier(int hp, std::pair<int, int> currentXy, int price, char type, int longes, int speed, bool who, std::string nameVessel);

public:
    Aircraft_carrier(std::pair<int, int>currentXy, char type, bool who, std::string nameVessel);

    Airplane* getAirplane();

    void setAirplane(Airplane* air);
    /**
     * @brief refresh ammunition airplane ,takes lung ammo from storage,if few of them take the rest
    */
    void refreshLung() override;
    /**
     * @brief refresh ammunition airplane ,takes heavy ammo from storage,if few of them take the rest
    */
    void refreshHeavy() override;
    /**
     * @brief change active airplane;
    */
    void startAirplane();

    ~Aircraft_carrier() {
        delete plane;
    }
};

