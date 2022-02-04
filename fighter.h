#pragma once

#include "Airplane.h"
#include "Parametres.h"

class Fighter : public Airplane {

public:

    Fighter(std::pair<int, int >currentXy, char type, bool who, Vessel* parent);
    /**
     * @brief 
     * @param M 
    */
    void attack(Object* M) override;

      ~Fighter() {
            delete mass;
    } 
};

