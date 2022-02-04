#include "Air_cruiser.h"

Air_cruiser::Air_cruiser(std::pair<int, int>currentXy, char type, bool who, std::string nameVessel) : Aircraft_carrier(hpAirCruiser, currentXy, priceAirCruiser, type, longesAirCruiser, speedAirCruiser, who, nameVessel), Armed_cruiser(attackHpAirCruiser, hpAirCruiser, currentXy, priceAirCruiser, type, longesAirCruiser, speedAirCruiser, who, nameVessel), Vessel(hpAirCruiser, currentXy, priceAirCruiser, type, longesAirCruiser, speedAirCruiser, who, nameVessel, new Warehouse(priceHeavyPatron, priceLungPatron)) {
}
void Air_cruiser::refreshLung() {
    Aircraft_carrier::refreshLung();
    Armed_cruiser::refreshLung();
};

void Air_cruiser::refreshHeavy() {
    Aircraft_carrier::refreshHeavy();
    Armed_cruiser::refreshHeavy();
};
void Air_cruiser::refreshLungAirplane() {
    Aircraft_carrier::refreshLung();
}
void Air_cruiser::refreshHeavyAirplane() {
    Aircraft_carrier::refreshHeavy();
}
void Air_cruiser::refreshLungCruiser() {
    Armed_cruiser::refreshLung();
}
void Air_cruiser::refreshHeavyCruiser() {
    Armed_cruiser::refreshHeavy();
}