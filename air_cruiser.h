#pragma once

#include "Aircraft_carrier.h"
#include "Armed_cruiser.h"

class Air_cruiser : public Aircraft_carrier, public Armed_cruiser {
private:


public:
    Air_cruiser(std::pair<int, int>currentXy, char type, bool who, std::string nameVessel) : Aircraft_carrier(hpAirCruiser, currentXy, priceAirCruiser, type, longesAirCruiser, speedAirCruiser, who, nameVessel) , Armed_cruiser(attackHpAirCruiser,hpAirCruiser, currentXy, priceAirCruiser, type, longesAirCruiser, speedAirCruiser, who, nameVessel), Vessel(hpAirCruiser, currentXy, priceAirCruiser, type, longesAirCruiser, speedAirCruiser, who, nameVessel, new Warehouse) {
    }

    void refreshLung() {
        Aircraft_carrier::refreshLung();
        Armed_cruiser::refreshLung();
    };
    void refreshHeavy() {
        Aircraft_carrier::refreshHeavy();
        Armed_cruiser::refreshHeavy();
    };

    void refreshLungAirplane() {
        Aircraft_carrier::refreshLung();
    }

    void refreshHeavyAirplane() {
        Aircraft_carrier::refreshHeavy();
    }

    void refreshLungCruiser(){
        Armed_cruiser::refreshLung();
    }


    void refreshHeavyCruiser() {
        Armed_cruiser::refreshHeavy();
    }

};

