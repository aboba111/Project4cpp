#pragma once

#include <iostream>
#include"Table.h"
#include"Parametres.h"

class Descriptor {
protected:
    Table* X=new Table;
    int countMyFinish=0;
    int countOponentFinish=0;
    int Mydamage=0;
    int Oponentdamage = 0;
    int numMyMoney=10000;
    int numOponentMoney = 10000;
    int MaxDamage = 4000;
    int MaxFinishVessel = 3;
public:
    int byObject(int x, bool who);


    void whoFinish(int x, bool who);

    void damage(int x, bool who);

    int win();
   
    Table* getDesk();
    void setDesk(Table* table);
    int getMyMoney();
    int getOponentMoney();
    int getMyDamage();

    int getOponentDamage();

    int getMyVessel();

    int getOponentVessel();

};

