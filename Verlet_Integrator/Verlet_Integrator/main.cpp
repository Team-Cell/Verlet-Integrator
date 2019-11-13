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

	VRectangle rectangles[4];
	VRectangle top_rectangle(0, -20, 100, 20);
	VRectangle left_rectangle(-20, 0, 20, 100);
	VRectangle right_rectangle(100, 0, 20, 100);
	VRectangle bottom_rectangle(0, 100, 100, 20);

	rectangles[0] = top_rectangle;
	rectangles[1] = left_rectangle;
	rectangles[2] = right_rectangle;
	rectangles[3] = bottom_rectangle;

	bool constant_acceleration;

	int firstopcionmenu = 0;
	int case_num = 0;
	bool bool_const_acc = false;
	char char_const_acc= 'A';

	while ((firstopcionmenu != 2) && (firstopcionmenu <= 3 || firstopcionmenu >= 0)) {

		//menu
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
					cout << "Which is the density of the particle?: " << endl;
					cin >> particle.density;
					cout << "Which is the area?: " << endl;
					cin >> particle.area;
				}
				if ((char_const_acc != 'y') && (char_const_acc != 'Y') && (char_const_acc != 'n') && (char_const_acc != 'N')) {
					cout << endl << "You entered an invalid answer." << endl;
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

			//main loop
			while (particle.pos.x <= 500 || particle.pos.y <= 500) {
				particle.pos = Verlet_Integration(particle.pos,particle.prev_pos,particle.a,1.0f);
				for (int i = 0; i < 4; i++)
				{
					if (CheckCollision(particle, rectangles[i])) cout << "Collision" << endl;
				}
			}

		}
		char_const_acc = 'A';
		cout << endl << endl;
	}
	return 0;
}
