#pragma once
#include"Aircraft_carrier.h"
#include "Aircraft_carrier.h"
#include "Armed_cruiser.h"

class Air_cruiser : public Aircraft_carrier, public Armed_cruiser {
private:


public:
    Air_cruiser(std::pair<int, int>currentXy, char type, bool who, std::string nameVessel);

    void refreshLung();
    void refreshHeavy();

    void refreshLungAirplane();

    void refreshHeavyAirplane();

    void refreshLungCruiser();


    void refreshHeavyCruiser();

};

