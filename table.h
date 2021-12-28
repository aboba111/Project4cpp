#pragma once
#include<iostream>
#include <vector>
#include "vessel.h"
#include "aircraft_carrier.h"
#include "armed_cruiser.h"
#include "fighter.h"
#include"stormtrooper.h"
#include"airplane.h"


const int weight = 32;
const int height = 16;
const int myMoney=700;
const int oponentMoney=800;

struct tableVessel {
	std::vector<aircraft_carrier*> Aircraft;
	std::vector<armed_cruiser*>Cruiser;
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
		if (getInfo(position, height - 2) == nullptr && getInfo(position, 1)==nullptr) {
			switch (type)
			{
			case'A': {
				aircraft_carrier* M = new aircraft_carrier;
				myVessel.Aircraft.push_back(M);
				tableMap[coordinateToIndex(position, height - 2)].allVessel = M;
				M->setCurrentXy(position, height - 2);
				M->setType(type);
				M->setName(Name);
				break;
			}

			case'B': {
				armed_cruiser* M = new armed_cruiser;
				myVessel.Cruiser.push_back(M);
				tableMap[coordinateToIndex(position, height - 2)].allVessel = M;
				M->setCurrentXy(position, height - 2);
				M->setType(type);
				M->setName(Name);
				break;
			}
			case'a': {
				aircraft_carrier* M = new aircraft_carrier;
				myOponentVessel.Aircraft.push_back(M);
				tableMap[coordinateToIndex(position, 1)].allVessel = M;
				M->setCurrentXy(position, 1);
				M->setType(type);
				M->setName(Name);
				break;
			}
			case'b': {
				armed_cruiser* M = new armed_cruiser;
				myOponentVessel.Cruiser.push_back(M);
				tableMap[coordinateToIndex(position, 1)].allVessel = M;
				M->setCurrentXy(position, 1);
				M->setType(type);
				M->setName(Name);
				break;
			}
			}
		}
	}

	void clean(){//очистка карты
		for (int i = 0;i < height * weight;i++) {
			if (i < 2 * weight) {
				tableMap[i].type='>';
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
			std::pair<int, int> xy = myOponentVessel.Aircraft[i]->getCurrentXy();
			show(myOponentVessel.Aircraft[i]->getType(), xy.first, xy.second);
			std::vector <stormtrooper*> S = myOponentVessel.Aircraft[i]->getStormtrooperAirplane();
			std::vector <fighter*> F= myOponentVessel.Aircraft[i]->getFighterAirplane();
			for (int j = 0;j < S.size();j++) {
				if (S[j]->getActive() == true) {
					show(S[j]->getType(), xy.first, xy.second);
				}
			}
			for (int j=0;j < F.size();j++) {
				if (F[j]->getActive() == true) {
					show(F[j]->getType(), xy.first, xy.second);
				}
			}

		}
		for (int i = 0;i < myVessel.Aircraft.size();i++) {
			std::pair<int, int> xy = myVessel.Aircraft[i]->getCurrentXy();
			show(myVessel.Aircraft[i]->getType(), xy.first, xy.second);
			std::vector <stormtrooper*> S = myVessel.Aircraft[i]->getStormtrooperAirplane();
			std::vector <fighter*> F = myVessel.Aircraft[i]->getFighterAirplane();
			for (int j = 0;j < S.size();j++) {
				if (S[j]->getActive() == true) {
					show(S[j]->getType(), xy.first, xy.second);
				}
			}
			for (int j = 0;j < F.size();j++) {
				if (F[j]->getActive() == true) {
					show(F[j]->getType(), xy.first, xy.second);
				}
			}
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


	int startAirplane(int x,int y,int num, char type) {
		aircraft_carrier* A;
		if (getInfo(x, y) == nullptr) {
			object* B = getInfo(x, y);
			aircraft_carrier* A = (aircraft_carrier*)B;
			if (type == 'C') {
				std::vector <stormtrooper*> S = A->getStormtrooperAirplane();
				S[num]->setCurrentXy(A->getCurrentXy().first + 1, A->getCurrentXy().second);
				S[num]->setActive(true);
				return 1;
			}
			if (type == 'F') {
				std::vector <fighter*> F = A->getFighterAirplane();
				F[num]->setCurrentXy(A->getCurrentXy().first + 1, A->getCurrentXy().second);
				F[num]->setActive(true);
				return 1;
			}

			if (type == 'c') {
				std::vector <stormtrooper*> S = A->getStormtrooperAirplane();
				S[num]->setCurrentXy(A->getCurrentXy().first + 1, A->getCurrentXy().second);
				S[num]->setActive(true);
				return 1;
			}
			if (type == 'f') {
				std::vector <fighter*> F = A->getFighterAirplane();
				F[num]->setCurrentXy(A->getCurrentXy().first + 1, A->getCurrentXy().second);
				F[num]->setActive(true);
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
		else {
			std::cout << "Cruiser:" << std::endl;
			for (int i = 0; i < myVessel.Cruiser.size();i++) {
				std::cout << i << " - Hp:" << myVessel.Cruiser[i]->getHp() << "	|	(" << myVessel.Cruiser[i]->getCurrentXy().first << "; " << myVessel.Cruiser[i]->getCurrentXy().second << ")" << std::endl;
			}
		}
	}

	void createRandomFlot(std::string who) {
		int costCarier = 100;
		if (who == "my") {
			int j = std::rand() % (myMoney / costCarier * 2);
			for (int i=0;i < j;i++) {
				if (std::rand() % 2) {
					addVessles('A', std::rand() % 32, "my");
				}
				else {
					addVessles('B', std::rand() % 32, "my");
				}
			}
		}
		else {
			int j = std::rand() % (oponentMoney / costCarier * 2);
			for (int i=0;i < j;i++) {
				if (std::rand() % 2) {
					addVessles('a', std::rand() % 32, "oponent");
				}
				else {
					addVessles('b', std::rand() % 32, "oponent");

				}
			}

		}
	}
};

