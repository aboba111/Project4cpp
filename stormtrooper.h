#pragma once

#include"Airplane.h"
#include "Parametres.h"
class Stormtrooper : public Airplane {
public:

    Stormtrooper(std::pair<int, int >currentXy, char type, bool who,
        Vessel* parent);

    void attack(Object* M) override;

   ~Stormtrooper(){
        delete mass;
    }
};

