#pragma once

#include<iostream>

class Object {
protected:
    int hp;
    std::pair<int, int> currentXy;
    int price;
    char type;
    int longes;
    int speed;
    bool who;
public:


    Object(int hp,
        std::pair <int, int> currentXy,
        int price,
        char type,
        int longes,
        int speed,
        bool who);

    virtual void move(char type,int x) = 0;

    void setType(char type);
    void setSpeed(int x);

    void setCurrentXy(int x, int y);

    bool getWho();

    std::pair<int, int> getCurrentXy();

    int getSpeed();

    void getDamage(int x);

    int getHp();

    char getType();

    int getPrice();


    int getLonges();

    void setWho(bool x);

};

