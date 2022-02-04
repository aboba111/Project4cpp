#pragma once

#include <iostream>
#include <vector>
#include "Vessel.h"
#include "Object.h"

class Airplane : public Object {
protected:
    bool active;
    Armament *mass;
    Vessel *parent;
    int attackHp;

public:

    Airplane(int hp, std::pair<int, int >currentXy, int price, char type, int longes, int attackHp, int speed, bool who,
        bool active,
        Armament* mass,
        Vessel* parent
    );

    bool getActive() const;
    /**
     * @brief checks attack conditions,if there are no those cartridges or there are no cartridges, it does not attack
     * @param X object being attacked
    */
    virtual void attack(Object *X) = 0;

    Armament* getMass();

    void setActive(bool active);

    Vessel* getParent();
    /**
     * @brief returns the address of the ship where the aircraft is stored
     * @param ves link vessel
    */
    void setParent(Vessel* ves);

    int getPrice();

    bool getActive();

    int getAttackHp();
    /**
   * @brief using the type determine how to move if x is not equal to speed,speed is x
   * @param type object
   * @param x parameter speed
  */
    void move(char type, int x) override;

    ~Airplane() {
     delete mass;
    }

};

