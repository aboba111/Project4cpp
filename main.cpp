#pragma once
#include<cmath>
#include"Table.h"
#include<iostream>
#include<windows.h>
#include"Airplane.h"
#include"Descriptor.h"
int stopVessel(int y1, int y2, int x, Table* table) {
	if (y2 > y1) {
		for (int i = 1; y1 + i <= y2;i++) {
			if (table->getInfo(x, y1 + i) != nullptr) {
				return i - 1;
			}
		}
	}
	else {
		for (int i = -1; y1 + i >= y2;i--) {
			if (table->getInfo(x, y1+ i) != nullptr) {
				return -i - 1;
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

void moveObject(Object* VesselXy, Table* table,int plan) {

	int x = VesselXy->getCurrentXy().first;
	int y = VesselXy->getCurrentXy().second;
	if (VesselXy->getType() == 'A' || VesselXy->getType() == 'B' ||  VesselXy->getType() == 'D'||plan==1 /*1 возращение вражеского корабля */) {
		int x1 = stopVessel(y, y - VesselXy->getSpeed(), x, table);
		if(plan==1)
		VesselXy->move(table->getInfo(x, y)->getType(), -stopVessel(y, y -VesselXy->getSpeed(), x, table));
		else
		VesselXy->move(table->getInfo(x, y)->getType(), stopVessel(y, y - VesselXy->getSpeed(), x, table));
		table->addVesselMap(x, y - stopVessel(y, y - VesselXy->getSpeed(), x, table), table->getInfo(x, y));
		if (x1!= 0)
		table->deleteVesselMap(x, y);
	}
	if (VesselXy->getType() == 'a' || VesselXy->getType() == 'b' || VesselXy->getType() == 'd' || plan == 2/*2 вылет вражеского корабля*/) {
		int x1 = stopVessel(y, y + VesselXy->getSpeed(), x, table);
		VesselXy->move(table->getInfo(x, y)->getType(), stopVessel(y, y + VesselXy->getSpeed(), x, table));
		table->addVesselMap(x, y + stopVessel(y, y + VesselXy->getSpeed(), x, table), table->getInfo(x, y));
		if(x1!=0)
		table->deleteVesselMap(x, y);
	}
	if (VesselXy->getType() == 'S' || VesselXy->getType() == 'C') {
		std::cout << "Enter the coordinates x y if the radius for the attack  is " << VesselXy->getSpeed() << std::endl;
		int x1;
		int y1;
		std::cin >> x1>> y1;
		if ((x1 - x< VesselXy->getSpeed() || x1 - x > -VesselXy->getSpeed()) && (y1 - y< VesselXy->getSpeed() || y1 - y > -VesselXy->getSpeed())) {
			if (table->getInfo(x1, y1) == nullptr) {
				table->getInfo(x,y)->setCurrentXy(x1, y1);
				table->addVesselMap(x1, y1, table->getInfo(x, y));
				if (stopVessel(x, x + VesselXy->getSpeed(), y, table) != 0)
				table->deleteVesselMap(x, y);
			}
			else {
				if (table->getInfo(x1, y1)->getType() == 'A') {
					Aircraft_carrier* A = dynamic_cast<Aircraft_carrier*>(table->getInfo(x1, y1));
					if (A->getAirplane() == nullptr){
						std::cout << "do you want teleport airplane 0)NO 1)Yes "<<std::endl;
						int k;
						std::cin >> k;
						if (k == 1) {
							Airplane* air = dynamic_cast<Airplane*>(VesselXy);
							A->setAirplane(air);
							air->setParent(A);
							air == nullptr;
						}
					}
				}
			}
		}
	}
			


}

//int attackAirplane(int x1, int y1, int x2, int y2, Table* X) {
//	if (x1 == x2) {
//		Aircraft_carrier* C = dynamic_cast<Aircraft_carrier*> (X->getInfo(x1, y1));
//	}
//	return 1;
//
//}


void randomMove(Table* X) {
	int i = std::rand() % 3;
	if (i == 0) {
		if (X->getMyOpponentVessel()->Aircraft.size() > 0) {
			Aircraft_carrier* M = X->getMyOpponentVessel()->Aircraft[std::rand() % X->getMyOpponentVessel()->Aircraft.size()];
			moveObject(M, X,0);
		}
	}
	if (i == 1) {
		if (X->getMyOpponentVessel()->Cruiser.size() > 0) {
			Armed_cruiser* M = X->getMyOpponentVessel()->Cruiser[std::rand() % X->getMyOpponentVessel()->Cruiser.size()];
			moveObject(M, X,0);
		}

	}
	if (i == 2) {
		if (X->getMyOpponentVessel()->AirCruiser.size() > 0) {
			Air_cruiser* M = X->getMyOpponentVessel()->AirCruiser[std::rand() % X->getMyOpponentVessel()->AirCruiser.size()];
			moveObject(M, X,0);
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



void del(Table* X, Object* objects) {
	if (objects->getHp() > 0)
		return;
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

int attack(Object* Objects, Table* X, bool flag) {
	int cize = foundEnemyObject(Objects, X).size();
	std::vector<Object*> objects = foundEnemyObject(Objects, X);
	if (objects.size() == 0)
		return;
	int x, y;
	if (flag == false) {
		x = objects[std::rand() % objects.size()]->getCurrentXy().first;
		y = objects[std::rand() % objects.size()]->getCurrentXy().second;

	}
	else {
		for (int i = 0;i < cize;i++) {
			std::cout << i << " - Hp:" << objects[i]->getHp() << "   	|	(" << objects[i]->getCurrentXy().first << "; " << objects[i]->getCurrentXy().second << ")" << std::endl;
		}
		std::cout << "Int Coordinate attack" << std::endl;
		if (cize != 0) {
			do {
				std::cin >> x >> y;
			} while (errorCoordinate(x, y, X));
		}
	}
	Object* M = X->getInfo(x, y);
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
	del(X, M);
	if (M->getHp() < 0)
		return M->getPrice();
	else return 0;

}

Object* randomAttack(Table* X) {
	std::vector<Object*>objects;
	for (int i = 0;i < X->getMyOpponentVessel()->Aircraft.size(); i++) {
		Aircraft_carrier* M = X->getMyOpponentVessel()->Aircraft[i];
		if (foundEnemyObject(M, X).size() > 0)
			objects.push_back(M);
		/*if (M->getAirplane()->getActive() == 1) {
			if (foundEnemyObject(M->getAirplane(), X).size() > 0)
				objects.push_back(M->getAirplane());
		}*/
	}
	for (int i = 0;i < X->getMyOpponentVessel()->AirCruiser.size(); i++) {
		Air_cruiser* M = X->getMyOpponentVessel()->AirCruiser[i];
		if (foundEnemyObject(M, X).size() > 0)
			objects.push_back(M);
		/*if (M->getAirplane()->getActive() == 1) {
			if (foundEnemyObject(M->getAirplane(), X).size() > 0)
				objects.push_back(M->getAirplane());
		}*/
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

void printAmmunition(Table* X) {
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
		std::cout << "Heavy pattron" << M->getHeavy()->getCurrentAmmunition()<<std::endl;
		std::cout << "Lung pattron" << M->getLung()->getCurrentAmmunition() << std::endl;
	}
	if (X->getInfo(x1, y1)->getType() == 'A') {
		Aircraft_carrier* M = dynamic_cast<Aircraft_carrier*>(X->getInfo(x1, y1));
		if(M->getAirplane()->getType()=='C')
		std::cout << "Heavy pattron" << M->getAirplane()->getMass()->getCurrentAmmunition() << std::endl;
		if (M->getAirplane()->getType() == 'S')
		std::cout << "Lung pattron" << M->getAirplane()->getMass()->getCurrentAmmunition() << std::endl;
	}
}
 



int moveOponentAirplaine(Table* X,Airplane* airplane,int &distance) {
	if (distance < 2) {
		int x1 = airplane->getCurrentXy().first;
		int y1 = airplane->getCurrentXy().second;
		moveObject(airplane, X, 2);
		int x2= airplane->getCurrentXy().first;
		int y2 = airplane->getCurrentXy().second;
		if (x1 != x2 || y1 != y2)
			distance++;
	}
	if (distance >= 2) {
		int x1 = airplane->getCurrentXy().first;
		int y1 = airplane->getCurrentXy().second;
		if (X->getInfo(x1, y1-1) != nullptr) {
			airplane->setActive(false);
			airplane->setCurrentXy(x1,y1 - 1);
			X->deleteVesselMap(x1, y1);
			return 1;
		}
		else
		moveObject(airplane, X, 1);

	}

	return 0;
}

int main() {
	int distance = 0;
	Airplane* airplane=nullptr;
	srand(time(nullptr));
	Descriptor desk;
	Table X =* desk.getDesk();
	Table X;
	int i = 0;
	//X.addVessels('A', 7, "ffd");
	//X.addVessels('a', 7, "ffd");
	//std::vector<Coordinate> y = X.getMap();
	//std::cout<<y[7 + 32 * 14].allVessel->getType();

//X.addVessels("A", "my", 5);
//X.refreshAllObjects();
	X.createRandomFlot("my");
	X.createRandomFlot("oponent");
	while (1) {
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
		std::cout << "7 recharg airplane" << std::endl;
		int s;
		std::cin >> s;
		switch (s)
		{
		case 1: {
			std::cout << "put Coordinate and type" << std::endl;
			
			int coordinate;
			char vesseles;
			std::cin >> coordinate >> vesseles;
			X.addVessels(vesseles, coordinate, "Object");
			desk.byObject(vesseles);
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
			std::cout << "select recharge type lung or heavy or heavy and lung";
			std::string typePattron;
			std::cin >> typePattron;
			if (typePattron == "lung") {
				M->refreshLung();
			}
			if (typePattron == "heavy") {
				M->refreshHeavy();
			}
			if (typePattron == "heavy and lung") {
				M->refreshLung();
				M->refreshHeavy();
			}
			desk.byPattron(M->getPrice());
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
			moveObject(X.getInfo(x1, y1), &X, 0);
			desk.win(K->getCurrentXy().second,true);
			break;

		}
		case 4: {
			std::cout << "put Coordinate " << std::endl;
			X.showMyObject('B');
			X.showMyObject('D');
			int x1;
			int y1;
			std::cout << "put Coordinate " << std::endl;
			do {
				std::cin >> x1 >> y1;
			} while (errorCoordinate(x1, y1, &X));
			desk.win(attack(X.getInfo(x1, y1), &X, true),false);
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
			printAmmunition(&X);
			std::cout << "put Coordinate " << std::endl;
			int x1;
			int y1;
			std::cout << "put Coordinate " << std::endl;
			do {
				std::cin >> x1 >> y1;
			} while (errorCoordinate(x1, y1, &X));
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


		if (randomAttack(&X)) {
			if (std::rand() % 3==1)
				attack(randomAttack(&X), &X, false);
		}
		else {
			if(std::rand() % 5 )
				randomMove(&X);
			else {
				if (airplane == nullptr) {
					TableVessel* tableVessel = X.getMyOpponentVessel();
					MyVector<Airplane*> A = X.returnAirplane(tableVessel,false);
					if (A.size() != 0) {
						int i = std::rand() % (A).size();
						int x = A[i]->getCurrentXy().first;
						int y = A[i]->getCurrentXy().second;
						X.startAirplane(x, y, A[i]->getType());
						airplane = A[i];
					}
				}
			}
		}
		if (airplane!=nullptr) {

			if (moveOponentAirplaine(&X, airplane, distance)) {
				airplane = nullptr;
				distance = 0;
			}
		}

		//attack(randomObject(&X),&X,false);
		//int cize = foundEnemyObject(X.getInfo(x1, y1), &X).size();
		//std::vector<Object*> objects = foundEnemyObject(X.getInfo(x1, y1), &X);
		system("cls");
		//std::cout << i++ << std::endl;
	}

	return 0;

}