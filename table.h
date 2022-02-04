#pragma once

#include<iostream>
#include <vector>

#include "Vessel.h"
#include "Aircraft_carrier.h"
#include "Armed_cruiser.h"
#include "Air_cruiser.h"

#include "Fighter.h"
#include "Stormtrooper.h"
#include "Airplane.h"
#include"MyVector.h"


const int weight = 32;
const int height = 16;
const int myMoney = 2000;
const int opponentMoney = 1500;

struct TableVessel {
    MyVector<Aircraft_carrier *> Aircraft;
    MyVector<Armed_cruiser *> Cruiser;
    MyVector<Air_cruiser *> AirCruiser;
};

struct Coordinate {
    char type;
    Object *allVessel;
};

class Table {

protected:

    struct TableVessel myVessel;
    struct TableVessel myOpponentVessel;
/*    struct Coordinate xyOpponentVessel;
    struct Coordinate xyMyVessel;*/

    std::vector<Coordinate> tableMap;

public:
    Table();
    /**
     * @brief overloaded operator outputs an array of character structures and pointers to ships
     * @param out takes values
     * @param map copy Table
     * @return out
    */
    friend std::ostream& operator<<(std::ostream& out, const Table& map);
    /**
     * @brief You, based on the type and position, a ship is created in a given coordinate, depending on the command, it will true or false,and vessel added to array TableVessel and Coordinate
     * @param type type vessel
     * @param position position vessel
     * @param name name vessel
    */
    void addVessels(char type, int position, const std::string& name);
    /**
     * @brief chang table map 
    */
    void clean();
    /**
     * @brief finds a cell in an array
     * @param x axis x
     * @param y axis y
     * @return index position x y
    */
    static int coordinateToIndex(int x, int y);
    /**
     * @brief show table use coordinate ,found in  
     * @param type vessel type
     * @param x 
     * @param y 
    */
    void show(char type, int x, int y);
    /**
     * @brief returns after clearing the symbolic display of objects
    */
    void refreshAllObjects();
    /**
     * @brief launches planes giving them coordinates
     * @param x vessel with airplane
     * @param y vessel with airplane
     * @param type airplane
     * @return 0 if have problem 1 if dont have problem
    */
    int startAirplane(int x, int y, char type);
    /**
     * @brief found object with coordinate
     * @param x axis x
     * @param y axis y
     * @return object pointer
    */
    Object* getInfo(int x, int y);

    /**
     * @brief delete object on mape
     * @param x coordinate oblect
     * @param y coordinate oblect
    */
    void deleteVesselMap(int x, int y);
    /**
     * @brief add object on mape
     * @param x coordinate oblect
     * @param y coordinate oblect
     * @param vessel 
    */
    void addVesselMap(int x, int y, Object* vessel);

    /**
     * @brief return map with objects
     * @return map
    */
    std::vector<Coordinate> getMap();
    /**
     * @brief show you object specific type and planes if this type has them
     * @param type you srr this type
    */
    void showMyObject(char type);
    /**
     * @brief 
     * main 
     * @param vessels  do vesel
     * @param active do active
     * @return 
    */
    MyVector<Airplane*> returnAirplane(TableVessel* vessels, bool active);
    /**
     * @brief creates a fleet for one of the teams
     * @param who teams
    */
    void createRandomFlot(const std::string& who);

    TableVessel* getMyOpponentVessel();

    TableVessel* getMyVessel();

};

