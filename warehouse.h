#pragma once

#include "Armament.h"

class Warehouse {
private:
    int heavyArmament = 1000;
    int lungArmament = 1000;
    int priceHeavyPatron;
    int priceLungPatron;

public:
    Warehouse(int priceHeavyPatron, int priceLungPatron); 
   
    void rechargeHeavy(int maxPatron);
      
    void rechargeLung(int maxPatron);
  
    int getSomePatronHeavy(int sizeMagazine);

    void AddPatronToWarehouse(int patron, std::string type);

    int getSomePatronLung(int sizeMagazine);


    void setHeavyArmament(int heavyArmament);

    void setLungArmament(int lungArmament);

    void byArmament(std::string type);

    int getHeavyCapacity();

    int getLungCapacity();
    int getHeavy();
    int getLung();
};

