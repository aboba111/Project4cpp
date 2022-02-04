#include "Object.h"

Object::Object(int hp,
    std::pair <int, int> currentXy,
    int price,
    char type,
    int longes,
    int speed,
    bool who) {
    this->hp = hp;
    this->currentXy = currentXy;
    this->price = price;
    this->type = type;
    this->longes = longes;
    this->speed = speed;
    this->who = who;

}


void Object::setType(char type) {
    this->type = type;
}

void Object::setSpeed(int x) {
    speed = x;
}

void Object::setCurrentXy(int x, int y) {
    this->currentXy.first = x;
    this->currentXy.second = y;
}

bool Object::getWho() {
    return who;
}

std::pair<int, int> Object::getCurrentXy() {
    return currentXy;
};

int Object::getSpeed() {
    return speed;
}

void Object::getDamage(int x) {
    this->hp -= x;
}

int Object::getHp() {
    return hp;
}

char Object::getType() {
    return type;
}
int Object::getPrice() {
    return price;
}

int Object::getLonges() {
    return longes;
}

void Object::setWho(bool x) {
    who = x;
}
