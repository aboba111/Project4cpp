#include "Airplane.h"
Airplane::Airplane(int hp, std::pair<int, int >currentXy, int price, char type, int longes, int attackHp, int speed, bool who,
    bool active,
    Armament* mass,
    Vessel* parent
) : Object(hp, currentXy, price, type, longes, speed, who) {
    this->active = false;
    this->mass = mass;
    this->parent = parent;
    this->attackHp = attackHp;
}

bool Airplane::getActive() const {
    return active;
}
Armament* Airplane::getMass() {
    return mass;
}
void Airplane::setActive(bool active) {
    this->active = active;
}
Vessel* Airplane::getParent() {
    return parent;
}
void Airplane::setParent(Vessel* ves) {
    this->parent = ves;
}
int Airplane::getPrice() {
    return price;
}
bool Airplane::getActive() {
    return active;
}
int Airplane::getAttackHp() {
    return attackHp;
}

void Airplane::move(char type, int x) {
    if (x <= speed) {
        if (type == 'C' || type == 'S') {
            this->currentXy.second -= x;
        }
        else
            this->currentXy.second += x;
    }
    else {
        if (type == 'C' || type == 'S') {
            this->currentXy.second -= speed;
        }
        else
            this->currentXy.second += speed;

    }

}