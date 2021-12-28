#pragma once
#include"table.h"
#include<iostream>
#include<windows.h>
#include"airplane.h"

int moveObject(object* VesselXy,table* table) {
	int x = VesselXy->getCurrentXy().first;
	int y = VesselXy->getCurrentXy().second;
		if (VesselXy->getType() == 'A' || VesselXy->getType() == 'B'|| VesselXy->getType() == 'S'|| VesselXy->getType() == 'C') {
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
		aircraft_carrier* C = (aircraft_carrier *) X->getInfo(x1, y1);
	}

	return 1;

}
int main() {
	table X;
	int i = 0;
		//X.addVessles('A', 7, "ffd");
		//X.addVessles('a', 7, "ffd");
		aircraft_carrier* C =(aircraft_carrier * )X.getInfo(7, 14);
		aircraft_carrier* S = (aircraft_carrier*)X.getInfo(7, 1);
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
		X.showMyObject('A');
		X.showMyObject('B');
		Sleep(1000);
		system("cls");
		//std::cout << i++ << std::endl;
	}

	return 0;

}