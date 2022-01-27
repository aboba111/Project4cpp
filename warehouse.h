#pragma once

#include "Armament.h"

class Warehouse {
private:
    int heavyArmament = 1000;
    int lungArmament = 1000;

public:
    void rechargeHeavy(int maxPatron) {
        heavyArmament -= maxPatron;
    }
      
    void rechargeLung(int maxPatron) {
        lungArmament -= maxPatron;
    }
  
    int getSomePatronHeavy(int sizeMagazine) {
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

    void AddPatronToWarehouse(int patron,std::string type) {
        if (type=="lung") {
            lungArmament += patron;
        }
        if (type == "heavy") {
            heavyArmament += patron;
        }

    }

    int getSomePatronLung(int sizeMagazine) {
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


    void setHeavyArmament(int heavyArmament) {
        this->heavyArmament = heavyArmament;
    }

    void setLungArmament(int lungArmament) {
        this->lungArmament = lungArmament;
    }

    void byArmament() {
        heavyArmament += 1000;
        lungArmament += 1000;
    }

    int getHeavyCapacity() {
        return heavyArmament;
    }

    int getLungCapacity() {
        return lungArmament;
    }
};

