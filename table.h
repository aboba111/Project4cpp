#pragma once
#include<iostream>
#include <vector>
#include "vessel.h"
#include "aircraft_carrier.h"
#include "armed_cruiser.h"
#include "fighter.h"
#include"stormtrooper.h"
#include"airplane.h"
#include"air_cruiser.h"


const int weight = 32;
const int height = 16;
const int myMoney=2000;
const int oponentMoney=1500;

struct tableVessel {
	std::vector<aircraft_carrier*> Aircraft;
	std::vector<armed_cruiser*>Cruiser;
	std::vector<air_cruiser*>AirCruiser;
};
struct coordinate {
	char type;
	object* allVessel;
};
class table
{

protected:
	struct tableVessel myVessel;
	struct tableVessel myOponentVessel;
	struct coordinate xyOponentVessel;
	struct coordinate xyMyVessel;

	std::vector<coordinate> tableMap;

public:
	table() {
		for (int i = 0;i < 2 * weight;i++) {
			struct coordinate X { '<', nullptr };
			tableMap.push_back(X);
		}
		for (int i = 0;i < weight * (height - 4);i++) {
			struct coordinate X { '.', nullptr };
			tableMap.push_back(X);
		}
		for (int i = 0;i < 2 * weight;i++) {
			struct coordinate X { '>', nullptr };
			tableMap.push_back(X);
		}
	}
	friend std::ostream& operator<<(std::ostream& out, const table& map) {
		for (int i = 0; i < weight * height;i++) {
			out << map.tableMap[i].type;
			if ((i + 1) % weight == 0) {
				out << std::endl;
			}
		}
		return out;
	}
	void addVessles(char type, int position, std::string Name) {
		switch (type)
		{
		case'A': {
			object* B;
			B = getInfo(position, height - 2);
			if (getInfo(position, height - 2) == nullptr) {
				aircraft_carrier* M = new aircraft_carrier;
				//aircraft_carrier* M = new aircraft_carrier(type, Name, {position,height-2},1);
				myVessel.Aircraft.push_back(M);
				tableMap[coordinateToIndex(position, height - 2)].allVessel = M;
				M->setCurrentXy(position, height - 2);
				M->setType(type);
				M->setName(Name);
				M->setWho(true);
			}
			break;
		}

		case'B': {
			if (getInfo(position, height - 2) == nullptr) {
				armed_cruiser* M = new armed_cruiser;
				myVessel.Cruiser.push_back(M);
				tableMap[coordinateToIndex(position, height - 2)].allVessel = M;
				M->setCurrentXy(position, height - 2);
				M->setType(type);
				M->setName(Name);
				M->setWho(true);
			}
			break;
		}
		case'D': {
			if (getInfo(position, height - 2) == nullptr) {
				air_cruiser* M = new air_cruiser;
				myVessel.AirCruiser.push_back(M);
				tableMap[coordinateToIndex(position, height - 2)].allVessel = M;
				M->setCurrentXy(position, height - 2);
				M->setType(type);
				M->setName(Name);
				M->setWho(true);
			}
			break;

		}
		case'a': {
			if (getInfo(position, 1) == nullptr) {
				aircraft_carrier* M = new aircraft_carrier;
				myOponentVessel.Aircraft.push_back(M);
				tableMap[coordinateToIndex(position, 1)].allVessel = M;
				M->setCurrentXy(position, 1);
				M->setType(type);
				M->setName(Name);
				M->setWho(false);
			}
			break;
		}
		case'b': {
			if (getInfo(position, 1) == nullptr) {
				armed_cruiser* M = new armed_cruiser;
				myOponentVessel.Cruiser.push_back(M);
				tableMap[coordinateToIndex(position, 1)].allVessel = M;
				M->setCurrentXy(position, 1);
				M->setType(type);
				M->setName(Name);
				M->setWho(false);
			}
			break;
		}
		case'd': {
			if (getInfo(position, 1) == nullptr) {
				air_cruiser* M = new air_cruiser;
				myOponentVessel.AirCruiser.push_back(M);
				tableMap[coordinateToIndex(position, 1)].allVessel = M;
				M->setCurrentXy(position, 1);
				M->setType(type);
				M->setName(Name);
				M->setWho(false);
			}
			break;
		}
	}
	}

	void clean(){//������� �����
		for (int i = 0;i < height * weight;i++) {
			if (i < 2 * weight) {
				tableMap[i].type='<';
			}
			if (i >= 2 * weight && i < (height - 2) * weight) {
				tableMap[i].type = '.';
			}
			if (i >= (height - 2) * weight) {
				tableMap[i].type = '>';

			}
			
		}
	}
	int coordinateToIndex(int x, int y) {
		return x + y * weight;
	}
	void show(char type, int x, int y) {
		tableMap[coordinateToIndex(x, y)].type = type;
	}
	void refreshAllObjects() {
		for (int i = 0;i < myOponentVessel.Aircraft.size();i++) {
			aircraft_carrier* M = myOponentVessel.Aircraft[i];
			std::pair<int, int> xy = myOponentVessel.Aircraft[i]->getCurrentXy();
			show(M->getType(), xy.first, xy.second);
			if (M->getAirplane() != nullptr)
			if (M->getAirplane()->getActive() == true) {
				std::pair<int, int> xyAirplane = M->getAirplane()->getCurrentXy();
				show(M->getAirplane()->getType(), xyAirplane.first, xyAirplane.second);
			}
		}
		for (int i = 0;i < myVessel.Aircraft.size();i++) {
			aircraft_carrier* M = myVessel.Aircraft[i];
			std::pair<int, int> xy = myVessel.Aircraft[i]->getCurrentXy();
			show(M->getType(), xy.first, xy.second);
			if (M->getAirplane() != nullptr)
			if (M->getAirplane()->getActive() == true) {
				std::pair<int, int> xyAirplane = M->getAirplane()->getCurrentXy();
				show(M->getAirplane()->getType(), xyAirplane.first, xyAirplane.second);
			}
		}
		for (int i = 0;i < myOponentVessel.AirCruiser.size();i++) {
			aircraft_carrier* M = myOponentVessel.AirCruiser[i];
			std::pair<int, int> xy = myOponentVessel.AirCruiser[i]->getCurrentXy();
			show(M->getType(), xy.first, xy.second);
			if (M->getAirplane() != nullptr)
			if (M->getAirplane()->getActive() == true) {
				std::pair<int, int> xyAirplane = M->getAirplane()->getCurrentXy();
				show(M->getAirplane()->getType(), xyAirplane.first, xyAirplane.second);
			}
		        for (int i = 0;i < myVessel.AirCruiser.size();i++) {
				aircraft_carrier* M = myVessel.AirCruiser[i];
				std::pair<int, int> xy = myVessel.AirCruiser[i]->getCurrentXy();
				show(M->getType(), xy.first, xy.second);
				if (M->getAirplane() != nullptr)
				if (M->getAirplane()->getActive() == true) {
					std::pair<int, int> xyAirplane = M->getAirplane()->getCurrentXy();
					show(M->getAirplane()->getType(), xyAirplane.first, xyAirplane.second);
				}

				for (int i = 0;i < myOponentVessel.Cruiser.size();i++) {
					std::pair<int, int> xy = myOponentVessel.Cruiser[i]->getCurrentXy();
					show(myOponentVessel.Cruiser[i]->getType(), xy.first, xy.second);
				}
				for (int i = 0;i < myVessel.Cruiser.size();i++) {
					std::pair<int, int> xy = myVessel.Cruiser[i]->getCurrentXy();
					show(myVessel.Cruiser[i]->getType(), xy.first, xy.second);
				}

			}
		}
	}



	int startAirplane(int x,int y, char type) {
		aircraft_carrier* A;
		if (getInfo(x, y) != nullptr) {
			object* B = getInfo(x, y);
			aircraft_carrier* A = dynamic_cast <aircraft_carrier*>(B);
			if (type == 'C' || type == 'S') {
				if (getInfo(x + 2, y) == nullptr) {
					airplane* Air = A->getAirplane();
					Air->setCurrentXy(A->getCurrentXy().first + 2, A->getCurrentXy().second);
					Air->setActive(true);
				}

				return 1;
			}
			if (type == 'c' || type == 's') {
				if (getInfo(x - 2, y) == nullptr) {
					airplane* Air = A->getAirplane();
					Air->setCurrentXy(A->getCurrentXy().first - 2, A->getCurrentXy().second);
					Air->setActive(true);
				}

				return 1;
			}
		}
		else return 0;
		}
	object* getInfo(int x, int y) {
		return tableMap[coordinateToIndex(x, y)].allVessel;
	};
	void deleteVesselMap(int x, int y) {
		tableMap[coordinateToIndex(x, y)].allVessel = nullptr;
	}
	void addVesselMap(int x, int y,object* vessel) {
		tableMap[coordinateToIndex(x, y)].allVessel =vessel;
	}
	std::vector<coordinate> getMap() {
		return tableMap;
	}
	
	void showMyObject(char type) {
		if (type == 'A') {
			std::cout << "Aircraft:" << std::endl;
			for (int i = 0; i < myVessel.Aircraft.size();i++) {
				std::cout << i << " - Hp:" << myVessel.Aircraft[i]->getHp() << "   	|	(" << myVessel.Aircraft[i]->getCurrentXy().first << "; " << myVessel.Aircraft[i]->getCurrentXy().second << ")" << std::endl;
			}
		}
		if (type =='B') {
			std::cout << "Cruiser:" << std::endl;
			for (int i = 0; i < myVessel.Cruiser.size();i++) {
				std::cout << i << " - Hp:" << myVessel.Cruiser[i]->getHp() << "	|	(" << myVessel.Cruiser[i]->getCurrentXy().first << "; " << myVessel.Cruiser[i]->getCurrentXy().second << ")" << std::endl;
			}
		}
		if (type=='D') {
			std::cout << "AirCruiser:" << std::endl;
			for (int i = 0; i < myVessel.AirCruiser.size();i++) {
				std::cout << i << " - Hp:" << myVessel.AirCruiser[i]->getHp() << "	|	(" << myVessel.AirCruiser[i]->getCurrentXy().first << "; " << myVessel.AirCruiser[i]->getCurrentXy().second << ")" << std::endl;
			}
		}
	}

	void createRandomFlot(std::string who) {
		int costCarier = 70;
		if (who == "my") {
			int j =( std::rand() % (myMoney / (costCarier) ));
			for (int i=0;i < j;i++) {
				int k;
				k = std::rand() % 3;
				if (k==0) {
					addVessles('A', std::rand() % weight, "my");
				}
				if(k== 1) {
					addVessles('B', std::rand() % weight, "my");
				}
				if(k== 2) {
					addVessles('D', std::rand() % weight, "my");
				}

			}
		}
		else {
			int j = (std::rand() % (oponentMoney / (costCarier) ))+5;
			for (int i=0;i < j;i++) {
				int k = std::rand() % 3;
				if (k==0) {
					addVessles('a', std::rand() % weight, "oponent");
				}
				if(k == 1) {
					addVessles('b', std::rand() % weight, "oponent");

				}
				if (k == 2) {
					addVessles('d', std::rand() % weight, "oponent");

				}
			}

		}
	}

	tableVessel* getMyOponentVessel() {
		return &myOponentVessel;
	}
	tableVessel* getMyVessel() {
		return &myVessel;
	}

};

