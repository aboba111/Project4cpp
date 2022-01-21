#pragma once
#include"table.h"
#include<iostream>
#include<windows.h>
#include"airplane.h"

int moveObject(object* VesselXy,table* table) {
	
	int x = VesselXy->getCurrentXy().first;
	int y = VesselXy->getCurrentXy().second;
		if (VesselXy->getType() == 'A' || VesselXy->getType() == 'B'|| VesselXy->getType() == 'S'|| VesselXy->getType() == 'C'|| VesselXy->getType() == 'D') {
			if (table->getInfo(x, y-1) == nullptr) {
				VesselXy->move(table->getInfo(x, y)->getType());
				table->addVesselMap(x, y - 1, table->getInfo(x, y));
				table->deleteVesselMap(x, y);
				return 0;
			}else{ return 1; }
		}
		else {
			if (table->getInfo(x, y + 1) == nullptr) {
				VesselXy->move(table->getInfo(x, y)->getType());
				table->addVesselMap(x, y + 1, table->getInfo(x, y));
				table->deleteVesselMap(x, y);
				//table.changMap(x, y);
				return 0;
			}else{ return 1; }
		}
}

int atackAirplane(int x1,int y1,int x2,int y2,table* X) {
	if (x1 == x2) {
		aircraft_carrier* C = dynamic_cast<aircraft_carrier *> (X->getInfo(x1, y1));
	}

	return 1;

}
void randomMove(table * X) {
	int i = std::rand() % 3;
	if (i==0) {
		if (X->getMyOponentVessel()->Aircraft.size() > 0) {
			aircraft_carrier* M = X->getMyOponentVessel()->Aircraft[std::rand() % X->getMyOponentVessel()->Aircraft.size()];
			moveObject(M, X);
		}
	}
	if (i==1) {
		if (X->getMyOponentVessel()->Cruiser.size()>0) {
			armed_cruiser* M = X->getMyOponentVessel()->Cruiser[std::rand() % X->getMyOponentVessel()->Cruiser.size()];
			moveObject(M, X);
		}

	}
	if (i == 2) {
		if (X->getMyOponentVessel()->AirCruiser.size() > 0) {
			air_cruiser* M = X->getMyOponentVessel()->AirCruiser[std::rand() % X->getMyOponentVessel()->AirCruiser.size()];
			moveObject(M, X);
		}

	}
}

//void attackOponent(table * X) {
//	std::vector<object>
//
//}
int erorCoordinate(int x, int y,table*X) {
	if (x < weight && x>= 0 && y < height && y >= 0) {
		if (X->getInfo(x, y)) {
			return 0;
		}
	}
	return 1;
}


//void myMove(table* X) {
//	std::cout << "choose a ship"<<std::endl;
//	int x, y;
//	std::cin >> x >> y;
//	moveObject(X->getInfo(x, y), X);
//}



std::vector<object*> foundEnemyObject(object *objects,table *X){
	std::vector<object*> vector;
	int x = objects->getCurrentXy().first;
	int y = objects->getCurrentXy().second;
	for (int i =x - objects->getLonges();i < x + objects->getLonges();i++) {
		for (int j = y - objects->getLonges();j < y + objects->getLonges();j++) {
			if(i>0 && j>0)
			if (X->getInfo(i,j)!=nullptr){
				if(objects->getWho()!=X->getInfo(i,j)->getWho())
				vector.push_back(X->getInfo(i,j));
			}


		}
	}
	return vector;
}


void del(table* X, object* objects) {
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
				for (int i = 0; i < X->getMyOponentVessel()->Cruiser.size(); i++) {
					if (X->getMyOponentVessel()->Cruiser[i] == objects) {
						X->getMyOponentVessel()->Cruiser.erase(X->getMyOponentVessel()->Cruiser.begin() + i);
						break;
					}
				}

			}
			armed_cruiser* M = dynamic_cast<armed_cruiser*>(objects);
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
				for (int i = 0; i < X->getMyOponentVessel()->AirCruiser.size(); i++) {
					if (X->getMyOponentVessel()->AirCruiser[i] == objects) {
						X->getMyOponentVessel()->AirCruiser.erase(X->getMyOponentVessel()->AirCruiser.begin() + i);
						break;
					}
				}

			}
			air_cruiser* M = dynamic_cast<air_cruiser*>(objects);
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
				for (int i = 0; i < X->getMyOponentVessel()->Aircraft.size(); i++) {
					if (X->getMyOponentVessel()->Aircraft[i] == objects) {
						X->getMyOponentVessel()->Aircraft.erase(X->getMyOponentVessel()->Aircraft.begin() + i);
						break;
					}
				}

			}
			aircraft_carrier* M = dynamic_cast<aircraft_carrier*>(objects);
			delete M;

		}
		if (objects->getType() == 'S' || objects->getType() == 's' || objects->getType() == 'C' || objects->getType() == 'c') {
			/*airplane* M = dynamic_cast<airplane*>(objects);
			dynamic_cast<aircraft_carrier*>(M->getParent())->setAirplane(nullptr);
			delete M;*/
		}


}

void atack(object* Objects,table *X,bool flag) {
	int cize = foundEnemyObject(Objects, X).size();
	std::vector<object*> objects = foundEnemyObject(Objects,X);
	if (objects.size()== 0)
		return;
	int x, y;
	if (flag == false){
		x=objects[std::rand() % objects.size()]->getCurrentXy().first;
		y = objects[std::rand() % objects.size()]->getCurrentXy().second;

	}
	else {
		for (int i = 0;i < cize;i++) {
			std::cout << i << " - Hp:" << objects[i]->getHp() << "   	|	(" << objects[i]->getCurrentXy().first << "; " << objects[i]->getCurrentXy().second << ")" << std::endl;
		}
		std::cout << "Int coordinate atack" << std::endl;
		if (cize != 0) {
			do {
				std::cin >> x >> y;
			} while (erorCoordinate(x, y, X));
		}
	}
	object* M = X->getInfo(x, y);
	if (Objects->getType() == 'B' || Objects->getType() == 'b' || Objects->getType() == 'D' || Objects->getType() == 'd') {
		if (Objects->getType() == 'B' || Objects->getType() == 'b') {
			armed_cruiser* K = dynamic_cast<armed_cruiser*> (Objects);
			if (M->getType() == 'A' || M->getType() == 'a') {
				if (K->getMass()->getCurrentLungAmmunition() == 0)
					return;
				else
					M->getDamage(Objects->getAtackHp());
			}
			else {
				if (K->getMass()->getCurrentHeavyAmmunition() == 0)
					return;
				else
					M->getDamage(Objects->getAtackHp());

			}
		}
		else {
			air_cruiser* K = dynamic_cast<air_cruiser*>(Objects);
			if (M->getType() == 'A' || M->getType() == 'a') {
				if (K->getMass()->getCurrentLungAmmunition() == 0)
					return;
				else
					M->getDamage(Objects->getAtackHp());
			}
			else {
				if (K->getMass()->getCurrentHeavyAmmunition() == 0)
					return;
				else
					M->getDamage(Objects->getAtackHp());

			}
		}
	}
	else {
		airplane* K = (airplane*)Objects;
		M->getDamage(K->attack(M));
	}
	
	del(X, M);
}





object* randomAttack(table* X) {
	std::vector<object*>objects;
	for (int i = 0;i < X->getMyOponentVessel()->Aircraft.size();i++) {
		aircraft_carrier* M = X->getMyOponentVessel()->Aircraft[i];
		if(foundEnemyObject(M,X).size()>0)
		objects.push_back(M);
		/*if (M->getAirplane()->getActive() == 1) {
			if (foundEnemyObject(M->getAirplane(), X).size() > 0)
				objects.push_back(M->getAirplane());
		}*/
	}
	for (int i = 0;i < X->getMyOponentVessel()->AirCruiser.size();i++) {
		air_cruiser* M = X->getMyOponentVessel()->AirCruiser[i];
		if (foundEnemyObject(M, X).size() > 0)
			objects.push_back(M);
		/*if (M->getAirplane()->getActive() == 1) {
			if (foundEnemyObject(M->getAirplane(), X).size() > 0)
				objects.push_back(M->getAirplane());
		}*/
	}
	for (int i = 0;i < X->getMyOponentVessel()->Cruiser.size();i++) {
		armed_cruiser* M = X->getMyOponentVessel()->Cruiser[i];
		if (foundEnemyObject(M, X).size() > 0)
			objects.push_back(M);
	}
	if (objects.size() == 0)
		return nullptr;
	return objects[std::rand()% objects.size()];

}

void printAmmunition(table *X) {
	int x1, y1;
	do {
		std::cout << "put coordinate " << std::endl;
		std::cin >> x1 >> y1;
	} while (erorCoordinate(x1, y1, X));
	if (X->getInfo(x1, y1)->getType() == 'B' || X->getInfo(x1, y1)->getType() == 'A' || X->getInfo(x1, y1)->getType() == 'D') {
		vessel* M = (vessel*)X->getInfo(x1, y1);
		std::cout << "Heavy Capacity" << std::endl;
		std::cout<<M->getWarehouse()->getHeavyCapacity()<<std::endl;
		std::cout << "Lung Capacity" << std::endl;
		std::cout <<M->getWarehouse()->getLungCapacity()<<std::endl;
	}
	if (X->getInfo(x1, y1)->getType() == 'B' || X->getInfo(x1, y1)->getType() == 'D') {

	}
}



int main() {
	srand(time(nullptr));
	table X;
	int i = 0;
		//X.addVessles('A', 7, "ffd");
		//X.addVessles('a', 7, "ffd");
		aircraft_carrier* C = dynamic_cast<aircraft_carrier * >(X.getInfo(7, 14));
		aircraft_carrier* S = dynamic_cast <aircraft_carrier*>(X.getInfo(7, 1));
		//std::vector<coordinate> y = X.getMap();
		//std::cout<<y[7 + 32 * 14].allVessel->getType();
	
	//X.addVessles("A", "my", 5);
	//X.refreshAllObjects();
		X.createRandomFlot("my");
		X.createRandomFlot("oponent");
	while (1) {
		X.clean();

		//moveObject(C, &X);
	    //moveObject(S, &X);
		X.refreshAllObjects();
		std::cout<<X;
		std::cout << "what you want" << std::endl;
		std::cout << "1 add object" << std::endl;
		std::cout << "2 add patron" << std::endl;
		std::cout << "3 went" << std::endl;
		std::cout << "4 attack" << std::endl;
		std::cout << "5 show my oblect" << std::endl;
		int s;
		std::cin >> s;
		switch (s)
		{
		case 1: {
			std::cout << "put coordinate and type" << std::endl;
			int coordinate;
			char vesseles;
			std::cin >> coordinate >> vesseles;
			X.addVessles(vesseles, coordinate, "object");
			break;
		}
		case 2: {
			std::cout << "chose object" << std::endl;
			X.showMyObject('A');
			X.showMyObject('B');
			X.showMyObject('D');
			int x1;
			int y1;
			std::string type;
			std::cin >> x1 >> y1;
			vessel* M = (vessel*)(X.getInfo(x1, y1));
			M->refreshAmmunition(type);
			break;
		}
		case 3: {
			std::cout << "put coordinate "<<std::endl;
			X.showMyObject('A');
			X.showMyObject('B');
			X.showMyObject('D');
			int x1;
			int y1;
			do {
				std::cout << "put coordinate " << std::endl;
				std::cin >> x1 >> y1;
			} while (erorCoordinate(x1, y1, &X));
			moveObject(X.getInfo(x1, y1), &X);
			break;
		
		}
		case 4: {
			std::cout << "put coordinate " << std::endl;
			X.showMyObject('B');
			X.showMyObject('D');
			int x1;
			int y1;
			std::cout << "put coordinate " << std::endl;
			do {
				std::cin >> x1 >> y1;
			} while (erorCoordinate(x1, y1, &X));
			atack( X.getInfo(x1, y1), &X, true);
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
	}
		
		if (randomAttack(&X)) {
			if(std::rand() % 2)
			randomMove(&X);
			else
			atack(randomAttack(&X), &X, false);
		}
		else
			randomMove(&X);
		
		//atack(randomObject(&X),&X,false);
		//int cize = foundEnemyObject(X.getInfo(x1, y1), &X).size();
		//std::vector<object*> objects = foundEnemyObject(X.getInfo(x1, y1), &X);
		system("cls");
		//std::cout << i++ << std::endl;
	}

	return 0;

}