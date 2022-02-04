#include "Warehouse.h"

Warehouse::Warehouse(int priceHeavyPatron, int priceLungPatron) {
    this->priceHeavyPatron = priceHeavyPatron;
    this->priceLungPatron = priceLungPatron;
}
void Warehouse::rechargeHeavy(int maxPatron) {
    heavyArmament -= maxPatron;
}

void Warehouse::rechargeLung(int maxPatron) {
    lungArmament -= maxPatron;
}

int Warehouse::getSomePatronHeavy(int sizeMagazine) {
    if (heavyArmament > 0) {
        if (heavyArmament / sizeMagazine > 0) {
            heavyArmament -= sizeMagazine;
            return sizeMagazine;
        }
        else {
            int res = heavyArmament % sizeMagazine;
            heavyArmament = 0;
            return res;
        }
    }
    return 0;
}

void Warehouse::AddPatronToWarehouse(int patron, std::string type) {
    if (type == "lung") {
        lungArmament += patron;
    }
    if (type == "heavy") {
        heavyArmament += patron;
    }

}

int Warehouse::getSomePatronLung(int sizeMagazine) {
    if (lungArmament > 0) {
        if (lungArmament / sizeMagazine > 0) {
            lungArmament -= sizeMagazine;
            return sizeMagazine;
        }
        else {
            int res = lungArmament % sizeMagazine;
            lungArmament = 0;
            return res;
        }
    }
    return 0;
}


void Warehouse::setHeavyArmament(int heavyArmament) {
    this->heavyArmament = heavyArmament;
}

void Warehouse::setLungArmament(int lungArmament) {
    this->lungArmament = lungArmament;
}

void Warehouse::byArmament(std::string type) {
    if (type == "Heavy")
        heavyArmament += 1000;
    if (type == "Lung")
        lungArmament += 1000;
}

int Warehouse::getHeavyCapacity() {
    return heavyArmament;
}

int Warehouse::getLungCapacity() {
    return lungArmament;
}
int Warehouse::getHeavy() {
    return priceHeavyPatron;
}
int Warehouse::getLung() {
    return priceLungPatron;
}
