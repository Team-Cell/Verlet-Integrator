#include <iostream>
#include <stdlib.h>
#include "Physics.h"
#include "Render.h"
#include "p2Log.h"
using namespace std;

int main(int argc, char* args[]) {

	LOG("Starting Integrator");

	Physics particle;

	int firstopcionmenu = 0;
	int case_num = 0;

	//Improve menu so different inputs can be taken

	while ((firstopcionmenu != 2) && (firstopcionmenu <= 3 || firstopcionmenu >= 0)) {
		cout << "MENU" << endl;
		cout << "What do you want to do?" << endl << "1- Execute the program" << endl << "2- Quit" << endl;
		cin >> firstopcionmenu;
		system("cls");
		if (firstopcionmenu == 1) {
			cout << "Which is the initial speed?:" << endl;
			cin >> particle.v.x >> particle.v.y;
			cout << "Which is the initial position?:" << endl;
			cin >> particle.pos.x >> particle.pos.y;
			cout << "Which is the initial acceleration?: " << endl;
			cin >> particle.a.x >> particle.a.y;
			cout << "Which is the time difference?: " << endl;
			cin >> particle.dt;
			cout << "Which is the mass?:" << endl;
			cin >> particle.m;
			system("cls");
			cout << "Case dt: " << particle.dt << " and a: " << particle.a.x << ", " << particle.a.y << endl;
			if (particle.a.IsZero() == true && particle.dt != 0)case_num = 1;
			else if (particle.a.IsZero() == false && particle.dt == 1)case_num = 2;
			else if (particle.a.IsZero() == false)case_num = 3;
			particle.InitialSituation(case_num);
			while (particle.pos.x <= 500 || particle.pos.y <= 500) {
				particle.Integrate();
			}
		}
	}
	return 0;
}
