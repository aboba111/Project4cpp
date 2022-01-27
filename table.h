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
    Table() {
        for (int i = 0; i < 2 * weight; i++) {
            struct Coordinate X{'<', nullptr};
            tableMap.push_back(X);
        }
        for (int i = 0; i < weight * (height - 4); i++) {
            struct Coordinate X{'.', nullptr};
            tableMap.push_back(X);
        }
        for (int i = 0; i < 2 * weight; i++) {
            struct Coordinate X{'>', nullptr};
            tableMap.push_back(X);
        }
    }

    friend std::ostream &operator<<(std::ostream &out, const Table &map) {
        for (int i = 0; i < weight * height; i++) {
            out << map.tableMap[i].type;
            if ((i + 1) % weight == 0) {
                out << std::endl;
            }
        }
        return out;
    }

    void addVessels(char type, int position, const std::string &name) {

        switch (type) {
            case 'A': {
                if (getInfo(position, height - 2) == nullptr) {
                    std::pair<int, int> xy{ position, height - 2 };
                    Aircraft_carrier *M = new Aircraft_carrier(xy,type,true,"myVessel");
                    tableMap[coordinateToIndex(position, height - 2)].allVessel = M;
                    tableMap[coordinateToIndex(position, height - 2)].type =type;
                    myVessel.Aircraft.push_back(M);
                }
                break;
            }
            case 'B': {
                if (getInfo(position, height - 2) == nullptr) {
                    std::pair<int, int> xy{ position, height - 2 };
                    Armed_cruiser *M = new Armed_cruiser(xy, type, true, "myVessel");
                    tableMap[coordinateToIndex(position, height - 2)].allVessel = M;
                    tableMap[coordinateToIndex(position, height - 2)].type = type;
                    myVessel.Cruiser.push_back(M);
                }
                break;
            }
            case 'D': {
                if (getInfo(position, height - 2) == nullptr) {
                    std::pair<int, int> xy{ position, height - 2 };
                    Air_cruiser *M = new Air_cruiser(xy, type, true, "myVessel");
                    myVessel.AirCruiser.push_back(M);
                    tableMap[coordinateToIndex(position, height - 2)].type = type;
                    tableMap[coordinateToIndex(position, height - 2)].allVessel = M;
                }
                break;

            }
            case 'a': {
                if (getInfo(position, 1) == nullptr) {
                    std::pair<int, int> xy{ position, 1 };
                    Aircraft_carrier *M = new Aircraft_carrier(xy, type, false, "myOponentVessel");
                    tableMap[coordinateToIndex(position, height - 2)].type = type;
                    myOpponentVessel.Aircraft.push_back(M);
                    tableMap[coordinateToIndex(position, 1)].allVessel = M;
                }
                break;
            }
            case 'b': {
                if (getInfo(position, 1) == nullptr) {
                    std::pair<int, int> xy{ position, 1 };
                    Armed_cruiser *M = new Armed_cruiser(xy, type, false, "myOponentVessel");
                    tableMap[coordinateToIndex(position, height - 2)].type = type;
                    myOpponentVessel.Cruiser.push_back(M);
                    tableMap[coordinateToIndex(position, 1)].allVessel = M;
                }
                break;
            }
            case 'd': {
                if (getInfo(position, 1) == nullptr) {
                    std::pair<int, int> xy{ position, 1 };
                    Air_cruiser *M = new Air_cruiser(xy, type, false, "myOponentVessel");
                    tableMap[coordinateToIndex(position, height - 2)].type = type;
                    tableMap[coordinateToIndex(position, 1)].allVessel = M;
                    myOpponentVessel.AirCruiser.push_back(M);
                }
                break;
            }
        }
    }

    void clean() {
        for (int i = 0; i < height * weight; i++) {
            if (i < 2 * weight) {
                tableMap[i].type = '<';
            }
            if (i >= 2 * weight && i < (height - 2) * weight) {
                tableMap[i].type = '.';
            }
            if (i >= (height - 2) * weight) {
                tableMap[i].type = '>';

            }

        }
    }

    static int coordinateToIndex(int x, int y) {
        return x + y * weight;
    }

    void show(char type, int x, int y) {
        tableMap[coordinateToIndex(x, y)].type = type;
    }

    void refreshAllObjects() {
        for (int i = 0; i < myOpponentVessel.Aircraft.size(); i++) {
            Aircraft_carrier *M = myOpponentVessel.Aircraft[i];
            std::pair<int, int> xy = myOpponentVessel.Aircraft[i]->getCurrentXy();
            show(M->getType(), xy.first, xy.second);
            if (M->getAirplane() != nullptr)
                if (M->getAirplane()->getActive()) {
                    std::pair<int, int> xyAirplane = M->getAirplane()->getCurrentXy();
                    show(M->getAirplane()->getType(), xyAirplane.first, xyAirplane.second);
                }
        }
        for (int i = 0; i < myVessel.Aircraft.size(); i++) {
            Aircraft_carrier *M = myVessel.Aircraft[i];
            std::pair<int, int> xy = myVessel.Aircraft[i]->getCurrentXy();
            show(M->getType(), xy.first, xy.second);
            if (M->getAirplane() != nullptr)
                if (M->getAirplane()->getActive()) {
                    std::pair<int, int> xyAirplane = M->getAirplane()->getCurrentXy();
                    show(M->getAirplane()->getType(), xyAirplane.first, xyAirplane.second);
                }
        }
        for (int i = 0; i < myOpponentVessel.AirCruiser.size(); i++) {
            Aircraft_carrier *M = myOpponentVessel.AirCruiser[i];
            std::pair<int, int> xy = myOpponentVessel.AirCruiser[i]->getCurrentXy();
            show(M->getType(), xy.first, xy.second);
            if (M->getAirplane() != nullptr)
                if (M->getAirplane()->getActive()) {
                    std::pair<int, int> xyAirplane = M->getAirplane()->getCurrentXy();
                    show(M->getAirplane()->getType(), xyAirplane.first, xyAirplane.second);
                }
            for (int i = 0; i < myVessel.AirCruiser.size(); i++) {
                Aircraft_carrier *M = myVessel.AirCruiser[i];
                std::pair<int, int> xy = myVessel.AirCruiser[i]->getCurrentXy();
                show(M->getType(), xy.first, xy.second);
                if (M->getAirplane() != nullptr)
                    if (M->getAirplane()->getActive()) {
                        std::pair<int, int> xyAirplane = M->getAirplane()->getCurrentXy();
                        show(M->getAirplane()->getType(), xyAirplane.first, xyAirplane.second);
                    }

                for (int i = 0; i < myOpponentVessel.Cruiser.size(); i++) {
                    std::pair<int, int> xy = myOpponentVessel.Cruiser[i]->getCurrentXy();
                    show(myOpponentVessel.Cruiser[i]->getType(), xy.first, xy.second);
                }
                for (int i = 0; i < myVessel.Cruiser.size(); i++) {
                    std::pair<int, int> xy = myVessel.Cruiser[i]->getCurrentXy();
                    show(myVessel.Cruiser[i]->getType(), xy.first, xy.second);
                }

            }
        }
    }

    int startAirplane(int x, int y, char type) {
        if (getInfo(x, y) != nullptr) {
            Object *B = getInfo(x, y);
            Aircraft_carrier *A = dynamic_cast <Aircraft_carrier *>(B);
            A->startAirplane();
            if (type == 'C' || type == 'S') {
                if (getInfo(x , y-2) == nullptr) {
                    Airplane *airplane = A->getAirplane();
                    airplane->setCurrentXy(A->getCurrentXy().first, A->getCurrentXy().second-2);
                    tableMap[coordinateToIndex(A->getCurrentXy().first, A->getCurrentXy().second - 2)].type = type;
                    tableMap[coordinateToIndex(A->getCurrentXy().first, A->getCurrentXy().second - 2)].allVessel = airplane;
                    
                }
                return 1;
            }
            if (type == 'c' || type == 's') {
                if (getInfo(x , y+2) == nullptr) {
                    Airplane *airplane = A->getAirplane();
                    airplane->setCurrentXy(A->getCurrentXy().first, A->getCurrentXy().second+2);
                    tableMap[coordinateToIndex(A->getCurrentXy().first, A->getCurrentXy().second + 2)].type = type;
                    tableMap[coordinateToIndex(A->getCurrentXy().first, A->getCurrentXy().second + 2)].allVessel = A;
                }
                return 1;
            }
        }
        return 0;
    }

    Object *getInfo(int x, int y) {
        return tableMap[coordinateToIndex(x, y)].allVessel;
    };

    void deleteVesselMap(int x, int y) {
        if(x<2)
        tableMap[coordinateToIndex(x, y)].type = '<';
        if (x > 14)
            tableMap[coordinateToIndex(x, y)].type = '>';
        if(x>=2||x<=14)
            tableMap[coordinateToIndex(x, y)].type = '.';
        tableMap[coordinateToIndex(x, y)].allVessel = nullptr;
    }

    void addVesselMap(int x, int y, Object *vessel) {
        tableMap[coordinateToIndex(x, y)].allVessel = vessel;
        tableMap[coordinateToIndex(x, y)].type = vessel->getType();

    }

    std::vector<Coordinate> getMap() {
        return tableMap;
    }

    void showMyObject(char type) {
        if (type == 'A') {
            std::cout << "Aircraft:" << std::endl;
            for (int i = 0; i < myVessel.Aircraft.size(); i++) {
                std::cout << i << " - Hp:" << myVessel.Aircraft[i]->getHp() << "   	|	("
                          << myVessel.Aircraft[i]->getCurrentXy().first << "; "
                          << myVessel.Aircraft[i]->getCurrentXy().second << ")" << std::endl;
            }
        }
        if (type == 'B') {
            std::cout << "Cruiser:" << std::endl;
            for (int i = 0; i < myVessel.Cruiser.size(); i++) {
                std::cout << i << " - Hp:" << myVessel.Cruiser[i]->getHp() << "	|	("
                          << myVessel.Cruiser[i]->getCurrentXy().first << "; "
                          << myVessel.Cruiser[i]->getCurrentXy().second << ")" << std::endl;
            }
        }
        if (type == 'D') {
            std::cout << "AirCruiser:" << std::endl;
            for (int i = 0; i < myVessel.AirCruiser.size(); i++) {
                std::cout << i << " - Hp:" << myVessel.AirCruiser[i]->getHp() << "	|	("
                          << myVessel.AirCruiser[i]->getCurrentXy().first << "; "
                          << myVessel.AirCruiser[i]->getCurrentXy().second << ")" << std::endl;
            }
        }
        if (type == 'D') {
            for (int i = 0; i < myVessel.AirCruiser.size(); i++) {
                if (myVessel.AirCruiser[i]->getAirplane() != nullptr) {
                    if (myVessel.AirCruiser[i]->getAirplane()->getActive() == true && myVessel.AirCruiser[i]->getAirplane()->getType() == 'S') {
                        std::cout << "Fighter:" << std::endl;
                        std::cout << i << " - Hp:" << myVessel.AirCruiser[i]->getHp() << "	|	("
                            << myVessel.AirCruiser[i]->getAirplane()->getCurrentXy().first << "; "
                            << myVessel.AirCruiser[i]->getAirplane()->getCurrentXy().second << ")" << std::endl;
                    }
                    if (myVessel.AirCruiser[i]->getAirplane()->getActive() == true && myVessel.AirCruiser[i]->getAirplane()->getType() == 'C') {
                        std::cout << "Stormtrooper:" << std::endl;
                        std::cout << i << " - Hp:" << myVessel.AirCruiser[i]->getHp() << "	|	("
                            << myVessel.AirCruiser[i]->getAirplane()->getCurrentXy().first << "; "
                            << myVessel.AirCruiser[i]->getAirplane()->getCurrentXy().second << ")" << std::endl;
                    }


                }
            }
        }
        if (type == 'A') {
            for (int i = 0; i < myVessel.Aircraft.size(); i++) {
                if (myVessel.Aircraft[i]->getAirplane() != nullptr) {
                    if (myVessel.Aircraft[i]->getAirplane()->getActive() == true && myVessel.Aircraft[i]->getAirplane()->getType() == 'C') {
                        std::cout << "Fighter:" << std::endl;
                        std::cout << i << " - Hp:" << myVessel.Aircraft[i]->getHp() << "	|	("
                            << myVessel.Aircraft[i]->getCurrentXy().first << "; "
                            << myVessel.Aircraft[i]->getCurrentXy().second << ")" << std::endl;
                    }
                    if (myVessel.Aircraft[i]->getAirplane()->getActive() == true && myVessel.Aircraft[i]->getAirplane()->getType() == 'S') {
                        std::cout << "Stormtrooper:" << std::endl;
                        std::cout << i << " - Hp:" << myVessel.Aircraft[i]->getHp() << "	|	("
                            << myVessel.Aircraft[i]->getAirplane()->getCurrentXy().first << "; "
                            << myVessel.Aircraft[i]->getAirplane()->getCurrentXy().second << ")" << std::endl;
                    }


                }
            }
        }
    }

    MyVector<Airplane*> returnAirplane(TableVessel *vessels,bool active) {
        MyVector<Airplane*> airplane;
        for (int i = 0; i < vessels->Aircraft.size(); i++) {
            if (vessels->Aircraft[i]->getAirplane() != nullptr) {
                if (vessels->Aircraft[i]->getAirplane()->getActive() == active) {
                    airplane.push_back(vessels->Aircraft[i]->getAirplane());
                }

            }
        }
        for (int i = 0; i < vessels->AirCruiser.size(); i++) {
            if (vessels->AirCruiser[i]->getAirplane() != nullptr) {
                if (vessels->AirCruiser[i]->getAirplane()->getActive() == active) {
                    airplane.push_back(vessels->AirCruiser[i]->getAirplane());
                }

            }
        }
        return airplane;
    }

    void createRandomFlot(const std::string& who) {
        int costCarrier = 70;
        if (who == "my") {
            int j = (rand() % (myMoney / (costCarrier)))+8;
            for (int i = 0; i < j; i++) {
                int k;
                k = rand() % 3;
                if (k == 0) {
                    addVessels('A', rand() % weight, "my");
                }
                if (k == 1) {
                    addVessels('B', rand() % weight, "my");
                }
                if (k == 2) {
                    addVessels('D', rand() % weight, "my");
                }

            }
        } else {
            int j = (rand() % (opponentMoney / (costCarrier))) + 8;
            for (int i = 0; i < j; i++) {
                int k = rand() % 3;
                if (k == 0) {
                    addVessels('a', rand() % weight, "oponent");
                }
                if (k == 1) {
                    addVessels('b', rand() % weight, "oponent");

                }
                if (k == 2) {
                    addVessels('d', rand() % weight, "oponent");

                }
            }

        }
    }

    TableVessel *getMyOpponentVessel() {
        return &myOpponentVessel;
    }

    TableVessel *getMyVessel() {
        return &myVessel;
    }

};

