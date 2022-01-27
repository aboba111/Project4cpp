#pragma once

#include <iostream>
#include"Table.h"
#include"Parametres.h"

class Descriptor {
protected:
    Table* X;
    int damage=0;
    int lostMoney = 0;
    int numMoney=10000;
    int coordinate = 2;
public:
    void byObject(char type) {
        if(type=='A')
        numMoney -=priceAircraft;
        if(type=='B')
        numMoney -= priceArmed;
        if(type=='D')
        numMoney -= priceAirCruiser;


    };

    void byPattron(int price) {
        numMoney-=price ;

    }
    void addDamage(int x) {
        lostMoney += x;
    }

    void win(int y,bool who) {
        if (who) {
            if (y < coordinate)
                std::cout << "you wine" << std::endl;
        }
        else {
            if (y <= 0)
                std::cout << "you lose" << std::endl;
        }

    };
   
    Table* getDesk() {
        return X;
    }
    int getMoney() {
        return numMoney;
    }

};

