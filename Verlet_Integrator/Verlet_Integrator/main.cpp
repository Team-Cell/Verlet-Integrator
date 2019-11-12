#include <iostream>
#include <stdlib.h>
#include "Verlet.h"
#include "Render.h"
#include "p2Log.h"
//#include "../SDL/include/SDL.h"
//#pragma comment( lib, "SDL/libx86/SDL2.lib" )
//#pragma comment( lib, "SDL/libx86/SDL2main.lib" )

using namespace std;

int main(int argc, char* args[]) {

	LOG("Starting Integrator");

	Verlet particle;
	bool constant_acceleration;

	int firstopcionmenu = 0;
	int case_num = 0;
	bool bool_const_acc = false;
	char char_const_acc= 'A';

	while ((firstopcionmenu != 2) && (firstopcionmenu <= 3 || firstopcionmenu >= 0)) {
		cout << "MENU" << endl;
		cout << "What do you want to do?" << endl << "1- Execute the program" << endl << "2- Quit" << endl;
		cin >> firstopcionmenu;
		system("cls");
		if (firstopcionmenu == 1) {
			cout << "Which is the initial position?:" << endl;
			cin >> particle.pos.x >> particle.pos.y;
			cout << "Which is the initial speed?:" << endl;
			cin >> particle.v.x >> particle.v.y;
			while ((char_const_acc != 'y') && (char_const_acc != 'Y') && (char_const_acc != 'n') && (char_const_acc != 'N')){
				cout << "Do you prefer a constant Acceleration?: " << endl << "(Yes: Y / No: N)" << endl;
				cin >> char_const_acc;
				if ((char_const_acc == 'y') || (char_const_acc == 'Y')) {
					bool_const_acc = true;
					cout << "Which is the initial acceleration?: " << endl;
					cin >> particle.a.x >> particle.a.y;
				}
				if ((char_const_acc == 'n') || (char_const_acc == 'N')) {
					bool_const_acc = false;
					cout << "Which is the aerodynamic drag coeficient?: " << endl;
					cin >> particle.drag_coeficient;
				}
				if ((char_const_acc != 'y') && (char_const_acc != 'Y') && (char_const_acc != 'n') && (char_const_acc != 'N')) {
					cout << endl << "You enter an invalid answer." << endl;
				}
			}
			cout << "Which is the mass?:" << endl;
			cin >> particle.mass;
			system("cls");
			cout << "Case dt: " << particle.dt << " and a: " << particle.a.x << ", " << particle.a.y << endl;
			if (particle.a.IsZero() == true && particle.dt != 0)case_num = 1;
			else if (particle.a.IsZero() == false && particle.dt == 1)case_num = 2;
			else if (particle.a.IsZero() == false)case_num = 3;
			InitialSituation(particle, case_num);
			while (particle.pos.y > 0) {
				particle.pos = Verlet_Integration(particle.pos,particle.prev_pos,particle.a,1.0f);
			}
		}
		char_const_acc = 'A';
		cout << endl << endl;
	}
	return 0;
}
