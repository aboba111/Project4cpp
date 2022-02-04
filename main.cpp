#pragma once
#include<cmath>
#include"Table.h"
#include<iostream>
#include<windows.h>
#include"Airplane.h"
#include"Descriptor.h"


/**
 * @brief deletes an object and everything in it,delete on map
 * @param X table
 * @param objects object to be deleted
*/
void del(Table* X, Object* objects) {
	std::cout << "dell";

	X->deleteVesselMap(objects->getCurrentXy().first, objects->getCurrentXy().second);
	if (objects->getType() == 'B' || objects->getType() == 'b') {
		if (objects->getType() == 'B') {
			for (int i = 0; i < X->getMyVessel()->Cruiser.size(); i++) {
				if (X->getMyVessel()->Cruiser[i] == objects) {
					X->getMyVessel()->Cruiser.erase(X->getMyVessel()->Cruiser.begin() + i);
					break;
				}
			}
		}
		else {
			for (int i = 0; i < X->getMyOpponentVessel()->Cruiser.size(); i++) {
				if (X->getMyOpponentVessel()->Cruiser[i] == objects) {
					X->getMyOpponentVessel()->Cruiser.erase(X->getMyOpponentVessel()->Cruiser.begin() + i);
					break;
				}
			}
		}
		Armed_cruiser* M = dynamic_cast<Armed_cruiser*>(objects);
		delete M;
	}
	if (objects->getType() == 'D' || objects->getType() == 'd') {
		if (objects->getType() == 'D') {
			for (int i = 0; i < X->getMyVessel()->AirCruiser.size(); i++) {
				if (X->getMyVessel()->AirCruiser[i] == objects) {
					X->getMyVessel()->AirCruiser.erase(X->getMyVessel()->AirCruiser.begin() + i);
					break;
				}
			}
		}
		else {
			for (int i = 0; i < X->getMyOpponentVessel()->AirCruiser.size(); i++) {
				if (X->getMyOpponentVessel()->AirCruiser[i] == objects) {
					X->getMyOpponentVessel()->AirCruiser.erase(X->getMyOpponentVessel()->AirCruiser.begin() + i);
					break;
				}
			}
		}
		Air_cruiser* M = dynamic_cast<Air_cruiser*>(objects);
		delete M;

	}
	if (objects->getType() == 'A' || objects->getType() == 'a') {
		if (objects->getType() == 'A') {
			for (int i = 0; i < X->getMyVessel()->Aircraft.size(); i++) {
				if (X->getMyVessel()->Aircraft[i] == objects) {
					X->getMyVessel()->Aircraft.erase(X->getMyVessel()->Aircraft.begin() + i);
					break;
				}
			}
		}
		else {
			for (int i = 0; i < X->getMyOpponentVessel()->Aircraft.size(); i++) {
				if (X->getMyOpponentVessel()->Aircraft[i] == objects) {
					X->getMyOpponentVessel()->Aircraft.erase(X->getMyOpponentVessel()->Aircraft.begin() + i);
					break;
				}
			}

		}
		Aircraft_carrier* M = dynamic_cast<Aircraft_carrier*>(objects);
		delete M;

	}
	if (objects->getType() == 'S' || objects->getType() == 's' || objects->getType() == 'C' || objects->getType() == 'c') {
		Airplane* M = dynamic_cast<Airplane*>(objects);
		dynamic_cast<Aircraft_carrier*>(M->getParent())->setAirplane(nullptr);
		delete M;
	}


}
/**
 * @brief checks if there are ships ahead
 * @param y1 start positon
 * @param y2 finish position 
 * @param x axis x
 * @param table game card
 * @return max long
*/
int stopVessel(int y1, int y2, int x, Table* table) {

	if (y2 > y1) {
		for (int i = 1; y1 + i <= y2;i++) {

			if (table->getInfo(x, y1 + i) != nullptr) {
				return i - 1;
			}
			if (y1+i >= height - 2) {
				return y2 - y1;
			}
		}
	}
	else {
		for (int i = -1; y1 + i >= y2;i--) {
			if (table->getInfo(x, y1+ i) != nullptr) {
				return -i - 1;
			}
			if (y1+i <=1) {
				return -y2 + y1;
			}
		}
	}
	if (y2 > y1) {
		return y2 - y1;
	}
	else {
		return y1 - y2;
	}
}
/**
 * @brief moves to the maximum allowed distance, if the ship has reached the end, removes it
 * @param vesselXy object
 * @param table game table
 * @param plan if 1 airplain run forward else back
 * @return point command
*/
std::pair<int,bool> moveObject(Object* vesselXy, Table* table,int plan) {
	std::cout << "moveobject";
	std::pair<int, bool>point;
	point.second = vesselXy->getWho();
	point.first = 0;
	int x = vesselXy->getCurrentXy().first;
	int y = vesselXy->getCurrentXy().second;
	std::cout << x << y << vesselXy->getType() << std::endl;
	Object* object = table->getInfo(x, y);
	if (vesselXy->getWho() == true&&stopVessel(y,y-vesselXy->getSpeed(),x,table)== vesselXy->getSpeed()) {
		if (y-vesselXy->getSpeed() <= 1) {
			point.first = 1;
			if (vesselXy->getType() == 'A' || vesselXy->getType() == 'D') {
				Aircraft_carrier* air = dynamic_cast<Aircraft_carrier*>(vesselXy);
				if (air->getAirplane() != nullptr) {
					point.first = 2;
				}
			}
			del(table, vesselXy);
			return point;
		}

	}
	if (vesselXy->getWho() == false&& stopVessel(y, y + vesselXy->getSpeed(), x, table) == vesselXy->getSpeed()) {
		if (y + vesselXy->getSpeed() >= height - 2) {
			point.first = 1;
			if (vesselXy->getType() == 'a' || vesselXy->getType() == 'd') {
				Aircraft_carrier* air = dynamic_cast<Aircraft_carrier*>(vesselXy);
				if (air->getAirplane() != nullptr) {
					point.first = 2;
				}
			}
			del(table, vesselXy);
			return point;
		}
	}

	if (vesselXy->getType() == 'A' || vesselXy->getType() == 'B' ||  vesselXy->getType() == 'D'||plan==1 /*1 возращение вражеского корабля */) {
		int longes = stopVessel(y, y - vesselXy->getSpeed(), x, table);
		if(plan==1)
		vesselXy->move(table->getInfo(x, y)->getType(), -longes);
		else
		vesselXy->move(table->getInfo(x, y)->getType(), longes);
		table->addVesselMap(x, y - longes,object);
		if (longes!= 0)
		table->deleteVesselMap(x, y);
	}
	if ((vesselXy->getType() == 'a' || vesselXy->getType() == 'b' || vesselXy->getType() == 'd' || plan == 2)/*2 вылет вражеского корабля*/) {
		int longes = stopVessel(y, y + vesselXy->getSpeed(), x, table);
		vesselXy->move(table->getInfo(x, y)->getType(),longes);
		table->addVesselMap(x, y + longes, object);
		if(longes!=0)
		table->deleteVesselMap(x, y);
	}
	if (vesselXy->getType() == 'S' || vesselXy->getType() == 'C') {
		std::cout << "Enter the coordinates x y if the radius for the attack  is " << vesselXy->getSpeed() << std::endl;
		int x1;
		int y1;
		std::cin >> x1>> y1;
		if ((x1 - x<= vesselXy->getSpeed() && x1 - x >= -vesselXy->getSpeed()) && (y1 - y<= vesselXy->getSpeed() && y1 - y >= -vesselXy->getSpeed())) {
			if (table->getInfo(x1, y1) == nullptr) {
				table->getInfo(x,y)->setCurrentXy(x1, y1);
				table->addVesselMap(x1, y1, table->getInfo(x, y));
				table->deleteVesselMap(x, y);
			}
			else {
				if (table->getInfo(x1, y1)->getType() == 'A'|| table->getInfo(x1, y1)->getType() == 'D') {
					Aircraft_carrier* A = dynamic_cast<Aircraft_carrier*>(table->getInfo(x1, y1));
					Airplane* air = dynamic_cast<Airplane*>(vesselXy);
					if (A == air->getParent()) {
						air->setActive(false);
						table->deleteVesselMap(x, y);
					}
					if (A->getAirplane() == nullptr){
						std::cout << "do you want teleport airplane 0)NO 1)Yes "<<std::endl;
						int k;
						std::cin >> k;
						if (k == 1) {
							A->setAirplane(air);
							air->setActive(false);
							air->setParent(A);
							air == nullptr;
						}
					}
				}
			}
		}
	}
			
	return point;

}

//int attackAirplane(int x1, int y1, int x2, int y2, Table* X) {
//	if (x1 == x2) {
//		Aircraft_carrier* C = dynamic_cast<Aircraft_carrier*> (X->getInfo(x1, y1));
//	}
//	return 1;
//
//}

/**
 * @brief selects an object and moves it
 * @param X table
 * @return point command
*/
std::pair<int,bool> randomMove(Table* X) {
	std::cout << "randommove";
	int i = std::rand() % 3;
	if (i == 0) {
		if (X->getMyOpponentVessel()->Aircraft.size() > 0) {
			Aircraft_carrier* M = X->getMyOpponentVessel()->Aircraft[std::rand() % X->getMyOpponentVessel()->Aircraft.size()];
			return moveObject(M, X,0);
		}
	}
	if (i == 1) {
		if (X->getMyOpponentVessel()->Cruiser.size() > 0) {
			Armed_cruiser* M = X->getMyOpponentVessel()->Cruiser[std::rand() % X->getMyOpponentVessel()->Cruiser.size()];
			return moveObject(M, X,0);
		}

	}
	if (i == 2) {
		if (X->getMyOpponentVessel()->AirCruiser.size() > 0) {
			Air_cruiser* M = X->getMyOpponentVessel()->AirCruiser[std::rand() % X->getMyOpponentVessel()->AirCruiser.size()];
			return moveObject(M, X,0);
		}

	}
}
/**
 * @brief reloads and buys weapons
 * @param X table
 * @param buy price point
 * @param numMoney current money
 * @param desk game menu
*/
void randomReacharg(Table* X,int buy,int numMoney,Descriptor* desk) {
	std::cout << "randomrecharge";
	int i = std::rand() % 3;
	if (i == 0) {
		if (X->getMyOpponentVessel()->Aircraft.size() > 0) {
			Aircraft_carrier* M = X->getMyOpponentVessel()->Aircraft[std::rand() % X->getMyOpponentVessel()->Aircraft.size()];
			M->refreshHeavy();
			M->refreshLung();
			if (buy == 1) {
				int j = std::rand() % 2;
				if (j == 0 && numMoney > M->getWarehouse()->getLung()) {
					M->byArmament("Lung");
					desk->byObject(M->getWarehouse()->getLung(), false);
				}
				if (j == 1 && numMoney > M->getWarehouse()->getHeavy()) {
					M->byArmament("Heavy");
					desk->byObject(M->getWarehouse()->getHeavy(), false);
				}
			}
		}
	}
	if (i == 1) {
		if (X->getMyOpponentVessel()->Cruiser.size() > 0) {
			Armed_cruiser* M = X->getMyOpponentVessel()->Cruiser[std::rand() % X->getMyOpponentVessel()->Cruiser.size()];
			M->refreshHeavy();
			M->refreshLung();
			if (buy == 1) {
				int j = std::rand() % 2;
				if (j == 0 && numMoney > M->getWarehouse()->getLung()) {
					M->byArmament("Lung");
					desk->byObject(M->getWarehouse()->getLung(), false);
				}
				if (j == 1 && numMoney > M->getWarehouse()->getHeavy()) {
					M->byArmament("Heavy");
					desk->byObject(M->getWarehouse()->getHeavy(), false);
				}
			}
		}

	}
	if (i == 2) {
		if (X->getMyOpponentVessel()->AirCruiser.size() > 0) {
			Air_cruiser* M = X->getMyOpponentVessel()->AirCruiser[std::rand() % X->getMyOpponentVessel()->AirCruiser.size()];
			int k = std::rand() % 2;
			if (k == 0) {
				M->refreshHeavyAirplane();
				M->refreshLungAirplane();
			}
			if (k == 1) {
				M->refreshHeavyCruiser();
				M->refreshLungCruiser();
			}
			if (buy == 1) {
				int j = std::rand() % 2;
				if (j == 0 && numMoney > M->getWarehouse()->getLung()) {
					M->byArmament("Lung");
					desk->byObject(M->getWarehouse()->getLung(), false);
				}
					if (j == 1 && numMoney > M->getWarehouse()->getHeavy()) {
						M->byArmament("Heavy");
						desk->byObject(M->getWarehouse()->getHeavy(), false);
					}
			}
		}

	}
}

//void attackOpponent(Table * X) {
//	std::vector<Object>
//
//}
int errorCoordinate(int x, int y, Table* X) {
	if (x < weight && x >= 0 && y < height && y >= 0) {
		if (X->getInfo(x, y)) {
			return 0;
		}
	}
	return 1;
}

//void myMove(Table* X) {
//	std::cout << "choose a ship"<<std::endl;
//	int x, y;
//	std::cin >> x >> y;
//	moveObject(X->getInfo(x, y), X);
//}

std::vector<Object*> foundEnemyObject(Object* objects, Table* X) {
	std::vector<Object*> vector;
	int x = objects->getCurrentXy().first;
	int y = objects->getCurrentXy().second;
	for (int i = x - objects->getLonges();i <= x + objects->getLonges();i++) {
		for (int j = y - objects->getLonges();j <= y + objects->getLonges();j++) {
			if (i >= 0 && j >= 0 && i<weight && j<height)
				if (X->getInfo(i, j) != nullptr) {
					if (objects->getWho() != X->getInfo(i, j)->getWho())
						vector.push_back(X->getInfo(i, j));
				}
		}
	}
	return vector;
}


/**
 * @brief implements damage and dell object
 * @param Objects implements damage
 * @param X game table
 * @param flag who attack
 * @return point command
*/
std::pair<int,bool> attack(Object * Objects, Table * X, bool flag) {
	std::cout << "attack";
	std::pair<int, bool>point;
	point.first = 0;
	point.second = Objects->getWho();
	int cize = foundEnemyObject(Objects, X).size();
	std::vector<Object*> objects = foundEnemyObject(Objects, X);
	if (objects.size() == 0) {
		point.second == Objects->getWho();
		return point;
	}
	int x, y;
	if (flag == false) {
		x = objects[std::rand() % objects.size()]->getCurrentXy().first;
		y = objects[std::rand() % objects.size()]->getCurrentXy().second;

	}
	else {
		for (int i = 0;i < cize;i++) {
			std::cout << i << " - Hp:" << objects[i]->getHp() << "   	|	(" << objects[i]->getCurrentXy().first << "; " << objects[i]->getCurrentXy().second << ")" << std::endl;
		}
		std::cout << "Coordinate" << std::endl;
		if (cize != 0) {
			do {
				std::cin >> x >> y;
			} while (errorCoordinate(x, y, X));
		}

	}
	Object* M = X->getInfo(x, y);
	int hp = M->getHp();
	if (Objects->getType() == 'B' || Objects->getType() == 'b' || Objects->getType() == 'D' || Objects->getType() == 'd') {
		if (Objects->getType() == 'B' || Objects->getType() == 'b') {
			Armed_cruiser* K = dynamic_cast<Armed_cruiser*> (Objects);
			K->attack(M);
		}
		else {
		Air_cruiser* K = dynamic_cast<Air_cruiser*>(Objects);
		K->attack(M);
		}
	}
	else {
		Airplane* K = (Airplane*)Objects;
		K->attack(M);
	}
	if (M->getHp() <= 0) {
		if (Objects->getType() == 'A' || Objects->getType() == 'a' || Objects->getType() == 'D' || Objects->getType() == 'd') {
			Aircraft_carrier* K = dynamic_cast<Aircraft_carrier*>(Objects);
			if (K->getAirplane() != nullptr)
				point.first = hp + K->getAirplane()->getHp();
		}
		else {
			point.first = hp;
		}
		del(X, M);
		
	}
	else {
		point.first = hp - M->getHp();
	}
	return point;
}
/**
 * @brief chooses a ship to attack 
 * @param X game table
 * @return ship
*/
Object* randomAttack(Table* X) {
	std::cout << "randomattack";
	std::vector<Object*>objects;
	for (int i = 0;i < X->getMyOpponentVessel()->Aircraft.size(); i++) {
		Aircraft_carrier* M = X->getMyOpponentVessel()->Aircraft[i];
		if (foundEnemyObject(M, X).size() > 0)
			objects.push_back(M);
		if (M->getAirplane() != nullptr)
		if (M->getAirplane()->getActive() == true) {
			if (foundEnemyObject(M->getAirplane(), X).size() > 0)
				objects.push_back(M->getAirplane());
		}
	}
	for (int i = 0;i < X->getMyOpponentVessel()->AirCruiser.size(); i++) {
		Air_cruiser* M = X->getMyOpponentVessel()->AirCruiser[i];
		if (foundEnemyObject(M, X).size() > 0)
			objects.push_back(M);
		if (M->getAirplane() != nullptr)
		if (M->getAirplane()->getActive() == true) {
			if (foundEnemyObject(M->getAirplane(), X).size() > 0)
				objects.push_back(M->getAirplane());
		}
	}
	for (int i = 0;i < X->getMyOpponentVessel()->Cruiser.size(); i++) {
		Armed_cruiser* M = X->getMyOpponentVessel()->Cruiser[i];
		if (foundEnemyObject(M, X).size() > 0)
			objects.push_back(M);
	}
	if (objects.size() == 0)
		return nullptr;
	return objects[std::rand() % objects.size()];

}
/**
 * @brief return all amunition ship and offers recharge
 * @param X  game table
 * @return ship
*/
Vessel* printAmmunition(Table* X) {
	X->showMyObject('A');
	X->showMyObject('B');
	X->showMyObject('D');

	int x1, y1;
	do {
		std::cout << "put Coordinate " << std::endl;
		std::cin >> x1 >> y1;
	} while (errorCoordinate(x1, y1, X));
	if (X->getInfo(x1, y1)->getType() == 'B' || X->getInfo(x1, y1)->getType() == 'A' || X->getInfo(x1, y1)->getType() == 'D') {
		Vessel* M = (Vessel*)X->getInfo(x1, y1);
		std::cout << "Heavy Capacity" << std::endl;
		std::cout << M->getWarehouse()->getHeavyCapacity() << std::endl;
		std::cout << "Lung Capacity" << std::endl;
		std::cout << M->getWarehouse()->getLungCapacity() << std::endl;
	}
	if (X->getInfo(x1, y1)->getType() == 'B' || X->getInfo(x1, y1)->getType() == 'D') {
		Armed_cruiser* M = dynamic_cast<Armed_cruiser*>(X->getInfo(x1, y1));
		std::cout << "Heavy pattron" << std::endl;
		std::cout<<M->getHeavy()->getCurrentAmmunition() << std::endl;
		std::cout << "Lung pattron" << std::endl;
		std::cout<<M->getLung()->getCurrentAmmunition() << std::endl;
	}
	if (X->getInfo(x1, y1)->getType() == 'A') {
		Aircraft_carrier* M = dynamic_cast<Aircraft_carrier*>(X->getInfo(x1, y1));
		if (M->getAirplane()->getType() == 'C')
		std::cout << "Heavy pattron" << std::endl;
		std::cout<<M->getAirplane()->getMass()->getCurrentAmmunition() << std::endl;
		if (M->getAirplane()->getType() == 'S')
		std::cout << "Lung pattron" << std::endl;
		std::cout<<M->getAirplane()->getMass()->getCurrentAmmunition() << std::endl;
	}
	Vessel* vessel = (Vessel*)(X->getInfo(x1, y1));
	return vessel;
}
 

/**
 * @brief is responsible for the automatic departure of the aircraft, on departure it has mission 1 on the return flight 2
 * @param X it is table
 * @param airplane plane that takes off
 * @param distance how long to fly
 * @return 
*/

int moveOponentAirplaine(Table* X,Airplane* airplane,int &distance) {
	std::cout << "moveairplane";
	if (distance < 2) {
		int x1 = airplane->getCurrentXy().first;
		int y1 = airplane->getCurrentXy().second;
		std::cout << x1<<y1<<"Air";
		if (moveObject(airplane, X, 2).first > 0) {
			return 1;
		}
		int x2= airplane->getCurrentXy().first;
		int y2 = airplane->getCurrentXy().second;
		if (x1 != x2 || y1 != y2)
			distance++;
	}
	if (distance >= 2) {
		int x1 = airplane->getCurrentXy().first;
		int y1 = airplane->getCurrentXy().second;
		std::cout << x1 << y1 << "air";
		if (X->getInfo(x1, y1-1) != nullptr) {
			airplane->setActive(false);
			airplane->setCurrentXy(x1,y1 - 1);
			std::cout << x1 << y1 << std::endl;
			X->deleteVesselMap(x1, y1);
			return 1;
		}
		else
			if (moveObject(airplane, X, 1).first > 0) {
				return 1;
			};

	}
	return 0;
}

int main() {
	int distance = 0;
	Airplane* airplane=nullptr;
	srand(time(nullptr));

	MyVector<int> A;
	Descriptor desk;
	Table X = *desk.getDesk();

	int i = 0;
	//X.addVessels('A', 7, "ffd");
	//X.addVessels('a', 7, "ffd");
	//std::vector<Coordinate> y = X.getMap();
	//std::cout<<y[7 + 32 * 14].allVessel->getType();

//X.addVessels("A", "my", 5);
//X.refreshAllObjects();
	int c = 1;
	X.createRandomFlot("my");
	X.createRandomFlot("oponent");
	while (c) {
		X.clean();

		//moveObject(C, &X);
		//moveObject(S, &X);
		X.refreshAllObjects();
		std::cout << X;
		std::cout << "what you want" << std::endl;
		std::cout << "1 add Object" << std::endl;
		std::cout << "2 add patron" << std::endl;
		std::cout << "3 went" << std::endl;
		std::cout << "4 attack" << std::endl;
		std::cout << "5 show my oblect" << std::endl;
		std::cout << "6 start airplane" << std::endl;
		std::cout << "7 recharg object" << std::endl;
		char statistics;
		std::cout << "Do you want see statistics Y N" << std::endl;
		std::cin >> statistics;
		if (statistics == 'Y') {
			std::cout << "my money (" << desk.getMyMoney() << ") my damage ( " << desk.getMyDamage() << ") my finish vessel (" << desk.getMyVessel() << ")" << std::endl;
			std::cout << "Oponent money (" << desk.getOponentMoney() << ") oponent damage ( " << desk.getOponentDamage() << ") oponent finish vessel (" << desk.getOponentVessel() << ")" << std::endl;
		}

		int s;
		std::cin >> s;
		switch (s)
		{
		case 1: {
			std::cout << "put Coordinate and type" << std::endl;
			int price = 0;
			int coordinate;
			char vesseles;
			std::cin >> coordinate >> vesseles;
			if (vesseles == 'A') {
				std::pair<int, int>xy{ 1,1 };
				Aircraft_carrier A(xy, 'A', true, "myVessel");
				price = A.getPrice();
			}
			if (vesseles == 'B') {
				std::pair<int, int>xy{ 1,1 };
				Armed_cruiser A(xy, 'B', true, "myVessel");
				price = A.getPrice();
			}
			if (vesseles == 'D') {
				std::pair<int, int>xy{ 1,1 };
				Air_cruiser A(xy, 'D', true, "myVessel");
				price = A.getPrice();
			}
			if (desk.byObject(price, true)) {
				X.addVessels(vesseles, coordinate, "Object");
			}
			break;
		}
		case 2: {
			std::cout << "chose Object" << std::endl;
			X.showMyObject('A');
			X.showMyObject('B');
			X.showMyObject('D');
			int x1;
			int y1;
			std::string type;
			std::cin >> x1 >> y1;
			Vessel* M = (Vessel*)(X.getInfo(x1, y1));
			std::cout << "select recharge type lung or heavy";
			std::string typePattron;
			std::cin >> typePattron;
			if (typePattron == "lung") {
				if(desk.byObject(M->getWarehouse()->getLung(),true))
				M->byArmament("Lung");
			}
			if (typePattron == "heavy") {
				if (desk.byObject(M->getWarehouse()->getHeavy(), true))
				M->byArmament("Heavy");
			}
			break;
		}
		case 3: {
			std::cout << "put Coordinate " << std::endl;
			X.showMyObject('A');
			X.showMyObject('B');
			X.showMyObject('D');
			int x1;
			int y1;
			do {
				std::cout << "put Coordinate " << std::endl;
				std::cin >> x1 >> y1;
			} while (errorCoordinate(x1, y1, &X));
			Object* K = X.getInfo(x1, y1);
			std::pair<int, bool>point= moveObject(X.getInfo(x1, y1), &X, 0);
			desk.whoFinish(point.first,point.second);
			desk.win();
			break;

		}
		case 4: {
			std::cout << "put Coordinate " << std::endl;
			X.showMyObject('A');
			X.showMyObject('B');
			X.showMyObject('D');
			int x1;
			int y1;
			std::cout << "put Coordinate " << std::endl;
			do {
				std::cin >> x1 >> y1;
			} while (errorCoordinate(x1, y1, &X));
			std::pair<int, bool> point = attack(X.getInfo(x1, y1), &X, true);
			desk.damage(point.first,point.second);
			getchar();
			getchar();
			break;
		}
		case 5: {
			X.showMyObject('A');
			X.showMyObject('B');
			X.showMyObject('D');
			getchar();
			getchar();
			break;
		}
		case 6: {
			int x1;
			int y1;
			if (X.getMyVessel()->Aircraft.size() == 0)
				break;
			int count = 0;
			std::cout << "Aircraft:" << std::endl;
			for (int i = 0; i < X.getMyVessel()->Aircraft.size(); i++) {
				if (X.getMyVessel()->Aircraft[i]->getAirplane() != nullptr)
					if (X.getMyVessel()->Aircraft[i]->getAirplane()->getActive() == false) {
						std::cout << i << " - Hp:" << X.getMyVessel()->Aircraft[i]->getHp() << "   	|	("
							<< X.getMyVessel()->Aircraft[i]->getCurrentXy().first << "; "
							<< X.getMyVessel()->Aircraft[i]->getCurrentXy().second << ")" << std::endl;
						count++;
					}
			}
			std::cout << "AirCruis:" << std::endl;
			for (int i = 0; i < X.getMyVessel()->AirCruiser.size(); i++) {
				if (X.getMyVessel()->AirCruiser[i]->getAirplane() != nullptr)
					if (X.getMyVessel()->AirCruiser[i]->getAirplane()->getActive() == false) {
						std::cout << i << " - Hp:" << X.getMyVessel()->AirCruiser[i]->getHp() << "   	|	("
							<< X.getMyVessel()->AirCruiser[i]->getCurrentXy().first << "; "
							<< X.getMyVessel()->AirCruiser[i]->getCurrentXy().second << ")" << std::endl;
						count++;
					}
			}
			if (count != 0) {
				do {
					std::cout << "put Coordinate x y " << std::endl;
					std::cin >> x1 >> y1;
				} while (errorCoordinate(x1, y1, &X));
				if (X.getInfo(x1, y1)->getType() == 'A') {
					Aircraft_carrier* M = dynamic_cast<Aircraft_carrier*>(X.getInfo(x1, y1));
					if (M->getAirplane() == nullptr)
						break;
					if (M->getAirplane()->getActive() != false)
						break;
					X.startAirplane(x1, y1, M->getAirplane()->getType());
				}
				if (X.getInfo(x1, y1)->getType() == 'D') {
					Air_cruiser* M = dynamic_cast<Air_cruiser*>(X.getInfo(x1, y1));
					if (M->getAirplane() == nullptr)
						break;
					if (M->getAirplane()->getActive() != false)
						break;
					X.startAirplane(x1, y1, M->getAirplane()->getType());
				}
			}
			break;

		}
		case 7: {
			int x1=-1;
			int y1=-1;
			int stop;
			do{
				std::cout << "You want choose object 0)No 1)Yes 2)Exit " << std::endl;
				std::cin >> stop;
				if (stop == 1) {
					Vessel* vessel = printAmmunition(&X);
					x1 = vessel->getCurrentXy().first;
					y1 = vessel->getCurrentXy().second;
				}
			} while (stop != 2 && stop != 0);
			if (stop == 2)
				break;
			if (x1 == -1 || y1 == -1)
				break;
			if (X.getInfo(x1, y1)->getType() == 'A' || X.getInfo(x1, y1)->getType() == 'B') {
				Vessel* vessel = dynamic_cast<Vessel*>(X.getInfo(x1, y1));
				vessel->refreshLung();
				vessel->refreshHeavy();
			}
			if (X.getInfo(x1, y1)->getType() == 'D') {
				std::cout << "chouse type 1)all 2)air 3)vessel" << std::endl;
				Air_cruiser* vessel = dynamic_cast<Air_cruiser*>(X.getInfo(x1, y1));
				int k;
				std::cin >> k;
				if (k == 1) {
					vessel->refreshHeavy();
					vessel->refreshLung();
				}
				if (k == 2) {
					vessel->refreshHeavyAirplane();
					vessel->refreshLungAirplane();
				}
				if (k == 3) {
					vessel->refreshHeavyCruiser();
					vessel->refreshLungCruiser();
				}

			}

		}
		}
		if (desk.win()) {
			c = 0;
		}

		if (randomAttack(&X)) {
			if (std::rand() % 3 == 1) {
				std::pair<int, bool>point = attack(randomAttack(&X), &X, false);
				desk.damage(point.first, point.second);
			}
		}
		if (std::rand() % 5) {
				std::pair<int, bool>point= randomMove(&X);
				desk.whoFinish(point.first, point.second);

		}
			if (std::rand() % 2) {
				int i = std::rand() % 2;
				randomReacharg(&X,i,desk.getOponentMoney(),&desk);
			}
			else {
				if (airplane == nullptr) {
					distance = 0;
					TableVessel* tableVessel = X.getMyOpponentVessel();
					MyVector<Airplane*> A = X.returnAirplane(tableVessel,false);
					if (A.size() != 0) {
						int i = std::rand() % (A).size();
						int x = A[i]->getParent()->getCurrentXy().first;
						int y = A[i]->getParent()->getCurrentXy().second;
						if (X.getInfo(x, y + 2) == nullptr && y + 2 < height - 2) {
							X.startAirplane(x, y, A[i]->getType());
								airplane = A[i];
						}
					}
				}
			}
		if (airplane!=nullptr) {
			std::cout << "moveOponentAirplaine";
			if (moveOponentAirplaine(&X, airplane, distance)) {
				airplane = nullptr;
				distance = 0;
			}
		}
		if (desk.win()) {
			c = 0;
		}
		else
			system("cls");
		
	
		//attack(randomObject(&X),&X,false);
		//int cize = foundEnemyObject(X.getInfo(x1, y1), &X).size();
		//std::vector<Object*> objects = foundEnemyObject(X.getInfo(x1, y1), &X);
		//std::cout << i++ << std::endl;
	}

	return 0;

}