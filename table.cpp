#include "Table.h"

Table::Table() {
    for (int i = 0; i < 2 * weight; i++) {
        struct Coordinate X { '<', nullptr };
        tableMap.push_back(X);
    }
    for (int i = 0; i < weight * (height - 4); i++) {
        struct Coordinate X { '.', nullptr };
        tableMap.push_back(X);
    }
    for (int i = 0; i < 2 * weight; i++) {
        struct Coordinate X { '>', nullptr };
        tableMap.push_back(X);
    }
}

 std::ostream& operator<<(std::ostream& out, const Table& map) {
    for (int i = 0; i < weight * height; i++) {
        out << map.tableMap[i].type;
        if ((i + 1) % weight == 0) {
            out << std::endl;
        }
    }
    return out;
}

void Table::addVessels(char type, int position, const std::string& name) {

    switch (type) {
    case 'A': {
        if (getInfo(position, height - 2) == nullptr) {
            std::pair<int, int> xy{ position, height - 2 };
            Aircraft_carrier* M = new Aircraft_carrier(xy, type, true, "myVessel");
            tableMap[coordinateToIndex(position, height - 2)].allVessel = M;
            tableMap[coordinateToIndex(position, height - 2)].type = type;
            myVessel.Aircraft.push_back(M);
        }
        break;
    }
    case 'B': {
        if (getInfo(position, height - 2) == nullptr) {
            std::pair<int, int> xy{ position, height - 2 };
            Armed_cruiser* M = new Armed_cruiser(xy, type, true, "myVessel");
            tableMap[coordinateToIndex(position, height - 2)].allVessel = M;
            tableMap[coordinateToIndex(position, height - 2)].type = type;
            myVessel.Cruiser.push_back(M);
        }
        break;
    }
    case 'D': {
        if (getInfo(position, height - 2) == nullptr) {
            std::pair<int, int> xy{ position, height - 2 };
            Air_cruiser* M = new Air_cruiser(xy, type, true, "myVessel");
            myVessel.AirCruiser.push_back(M);
            tableMap[coordinateToIndex(position, height - 2)].type = type;
            tableMap[coordinateToIndex(position, height - 2)].allVessel = M;
        }
        break;

    }
    case 'a': {
        if (getInfo(position, 1) == nullptr) {
            std::pair<int, int> xy{ position, 1 };
            Aircraft_carrier* M = new Aircraft_carrier(xy, type, false, "myOponentVessel");
            tableMap[coordinateToIndex(position, height - 2)].type = type;
            myOpponentVessel.Aircraft.push_back(M);
            tableMap[coordinateToIndex(position, 1)].allVessel = M;
        }
        break;
    }
    case 'b': {
        if (getInfo(position, 1) == nullptr) {
            std::pair<int, int> xy{ position, 1 };
            Armed_cruiser* M = new Armed_cruiser(xy, type, false, "myOponentVessel");
            tableMap[coordinateToIndex(position, height - 2)].type = type;
            myOpponentVessel.Cruiser.push_back(M);
            tableMap[coordinateToIndex(position, 1)].allVessel = M;
        }
        break;
    }
    case 'd': {
        if (getInfo(position, 1) == nullptr) {
            std::pair<int, int> xy{ position, 1 };
            Air_cruiser* M = new Air_cruiser(xy, type, false, "myOponentVessel");
            tableMap[coordinateToIndex(position, height - 2)].type = type;
            tableMap[coordinateToIndex(position, 1)].allVessel = M;
            myOpponentVessel.AirCruiser.push_back(M);
        }
        break;
    }
    }
}

void Table::clean() {
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

 int Table::coordinateToIndex(int x, int y) {
    return x + y * weight;
}

void Table::show(char type, int x, int y) {
    tableMap[coordinateToIndex(x, y)].type = type;
}

void Table::refreshAllObjects() {
    for (int i = 0; i < myOpponentVessel.Aircraft.size(); i++) {
        Aircraft_carrier* M = myOpponentVessel.Aircraft[i];
        std::pair<int, int> xy = myOpponentVessel.Aircraft[i]->getCurrentXy();
        show(M->getType(), xy.first, xy.second);
        if (M->getAirplane() != nullptr)
            if (M->getAirplane()->getActive()) {
                std::pair<int, int> xyAirplane = M->getAirplane()->getCurrentXy();
                show(M->getAirplane()->getType(), xyAirplane.first, xyAirplane.second);
            }
    }
    for (int i = 0; i < myVessel.Aircraft.size(); i++) {
        Aircraft_carrier* M = myVessel.Aircraft[i];
        std::pair<int, int> xy = myVessel.Aircraft[i]->getCurrentXy();
        show(M->getType(), xy.first, xy.second);
        if (M->getAirplane() != nullptr)
            if (M->getAirplane()->getActive()) {
                std::pair<int, int> xyAirplane = M->getAirplane()->getCurrentXy();
                show(M->getAirplane()->getType(), xyAirplane.first, xyAirplane.second);
            }
    }
    for (int i = 0; i < myOpponentVessel.AirCruiser.size(); i++) {
        Aircraft_carrier* M = myOpponentVessel.AirCruiser[i];
        std::pair<int, int> xy = myOpponentVessel.AirCruiser[i]->getCurrentXy();
        show(M->getType(), xy.first, xy.second);
        if (M->getAirplane() != nullptr)
            if (M->getAirplane()->getActive()) {
                std::pair<int, int> xyAirplane = M->getAirplane()->getCurrentXy();
                show(M->getAirplane()->getType(), xyAirplane.first, xyAirplane.second);
            }
    }
    for (int i = 0; i < myVessel.AirCruiser.size(); i++) {
        Aircraft_carrier* M = myVessel.AirCruiser[i];
        std::pair<int, int> xy = myVessel.AirCruiser[i]->getCurrentXy();
        show(M->getType(), xy.first, xy.second);
        if (M->getAirplane() != nullptr)
            if (M->getAirplane()->getActive()) {
                std::pair<int, int> xyAirplane = M->getAirplane()->getCurrentXy();
                show(M->getAirplane()->getType(), xyAirplane.first, xyAirplane.second);
            }
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

int Table::startAirplane(int x, int y, char type) {
    if (getInfo(x, y) != nullptr) {
        Object* B = getInfo(x, y);
        Aircraft_carrier* A = dynamic_cast <Aircraft_carrier*>(B);
        if (type == 'C' || type == 'S') {
            if (getInfo(x, y - 2) == nullptr && y - 2 > 1) {
                A->startAirplane();
                Airplane* airplane = A->getAirplane();
                airplane->setCurrentXy(A->getCurrentXy().first, A->getCurrentXy().second - 2);
                tableMap[coordinateToIndex(x, y - 2)].type = type;
                tableMap[coordinateToIndex(x, y - 2)].allVessel = airplane;
                return 1;
            }
            else
                return 0;
        }
        if (type == 'c' || type == 's') {
            if (getInfo(x, y + 2) == nullptr && y + 2 < height - 2) {
                A->startAirplane();
                Airplane* airplane = A->getAirplane();
                airplane->setCurrentXy(A->getCurrentXy().first, A->getCurrentXy().second + 2);
                tableMap[coordinateToIndex(x, y + 2)].type = type;
                tableMap[coordinateToIndex(x, y + 2)].allVessel = airplane;
                return 1;
            }
            else
                return 0;
        }
    }
    return 0;
}

Object* Table::getInfo(int x, int y) {
    return tableMap[coordinateToIndex(x, y)].allVessel;
};

void Table::deleteVesselMap(int x, int y) {
    if (x < 2)
        tableMap[coordinateToIndex(x, y)].type = '<';
    if (x > 14)
        tableMap[coordinateToIndex(x, y)].type = '>';
    if (x >= 2 || x <= 14)
        tableMap[coordinateToIndex(x, y)].type = '.';
    tableMap[coordinateToIndex(x, y)].allVessel = nullptr;
}

void Table::addVesselMap(int x, int y, Object* vessel) {
    tableMap[coordinateToIndex(x, y)].allVessel = vessel;
    if (vessel == nullptr)
        std::cout << "addVesselMap";
    tableMap[coordinateToIndex(x, y)].type = vessel->getType();

}

std::vector<Coordinate> Table::getMap() {
    return tableMap;
}

void Table::showMyObject(char type) {
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

MyVector<Airplane*> Table::returnAirplane(TableVessel* vessels, bool active) {
    MyVector<Airplane*> airplane;
    for (int i = 0; i < vessels->Aircraft.size(); i++) {
        if (vessels->Aircraft[i] == nullptr)
            std::cout << "returnAirplane";
        if (vessels->Aircraft[i]->getAirplane() != nullptr) {
            if (vessels->Aircraft[i]->getAirplane()->getActive() == active) {
                airplane.push_back(vessels->Aircraft[i]->getAirplane());
            }

        }
    }
    for (int i = 0; i < vessels->AirCruiser.size(); i++) {
        if (vessels->AirCruiser[i]->getAirplane() != nullptr) {
            if (vessels->AirCruiser[i] == nullptr)
                std::cout << "returnAirplane";
            if (vessels->AirCruiser[i]->getAirplane()->getActive() == active) {
                airplane.push_back(vessels->AirCruiser[i]->getAirplane());
            }

        }
    }
    return airplane;
}

void Table::createRandomFlot(const std::string& who) {
    int costCarrier = 70;
    if (who == "my") {
        int j = (rand() % (myMoney / (costCarrier))) + 8;
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
    }
    else {
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

TableVessel* Table::getMyOpponentVessel() {
    return &myOpponentVessel;
}

TableVessel* Table::getMyVessel() {
    return &myVessel;
}