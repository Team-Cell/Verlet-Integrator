#include <iostream>
#include <stdlib.h>
#include "Verlet.h"
#include "Render.h"
#include "p2Log.h"
#include "SDL/include/SDL.h"
#include "SDL_Image/include/SDL_image.h"

#pragma comment(lib, "SDL_Image/libx86/SDL2_image.lib")
#pragma comment(lib, "SDL/libx86/SDL2.lib")
#pragma comment(lib, "SDL/libx86/SDL2main.lib")

using namespace std;

int main(int argc, char* args[]) {

	LOG("Starting Integrator");
	int loop_counter = 0;

	Verlet particle;

	ModuleRender render;

	VRectangle rectangles[4];
	int rectangle_thickness = 200;
	VRectangle top_rectangle(0, -SCREEN_HEIGHT, SCREEN_WIDTH, rectangle_thickness);
	VRectangle left_rectangle(-rectangle_thickness, 0, rectangle_thickness,SCREEN_HEIGHT);
	VRectangle right_rectangle(SCREEN_WIDTH, 0, rectangle_thickness, SCREEN_HEIGHT);
	VRectangle bottom_rectangle(0, SCREEN_HEIGHT, SCREEN_WIDTH, rectangle_thickness);

	render.Init();

	rectangles[0] = top_rectangle;
	rectangles[1] = left_rectangle;
	rectangles[2] = right_rectangle;
	rectangles[3] = bottom_rectangle;

	int firstopcionmenu = 0;
	float time = 0;
	char char_const_acc= 'A';
	bool constant_acceleration;
	float dt = 0.1f;

	render.blit_all(0, 0);

	while ((firstopcionmenu != 2) && (firstopcionmenu <= 3 || firstopcionmenu >= 0)) {
		render.Init();
		//menu
		cout << "MENU" << endl;
		cout << "What do you want to do?" << endl << "1- Execute the program" << endl << "2- Quit" << endl;
		cin >> firstopcionmenu;
		system("cls");
		if (firstopcionmenu == 1) {
			cout << "Which is the initial position?:" << endl;
			cin >> particle.pos.x >> particle.pos.y;
			particle.pos.y = SCREEN_HEIGHT -particle.pos.y;
			cout << "Which is the initial speed?:" << endl;
			cin >> particle.v.x >> particle.v.y;
			particle.v.y = -particle.v.y;
			while ((char_const_acc != 'y') && (char_const_acc != 'Y') && (char_const_acc != 'n') && (char_const_acc != 'N')){
				cout << "Do you want gravity to be the only acceleration?: " << endl << "(Yes: Y / No: N)" << endl;
				cin >> char_const_acc;
				if ((char_const_acc == 'y') || (char_const_acc == 'Y')) {
					//cout << "Which is the initial acceleration?: " << endl;
					//cin >> particle.a.x >> particle.a.y;
					//particle.a.y = -particle.a.y;
					cout << "Which is the gravity?" << endl;
					cin >> particle.gravity;
					particle.gravity = -particle.gravity;
				}
				if ((char_const_acc == 'n') || (char_const_acc == 'N')) {
					cout << "Which is the gravity?" << endl;
					cin >> particle.gravity;
					particle.gravity = -particle.gravity;
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
			/*
			if (particle.a.IsZero() == true && particle.dt != 0)case_num = 1;
			else if (particle.a.IsZero() == false && particle.dt == 1)case_num = 2;
			else if (particle.a.IsZero() == false)case_num = 3;
			*/

			InitialSituation(particle, dt);

			//main loop
			while (loop_counter < 40) {
				particle.a = AccelerationSum(particle);
				particle.pos = Verlet_Integration(particle.pos,particle.prev_pos,particle.a,dt);
				for (int i = 0; i < 4; i++)
				{
					if (CheckCollision(particle, rectangles[i])) {
						cout << "Collision" << endl;
						time+=CalculateCollisionPosition(particle, rectangles[i]);
					}
				}
				if (time > 0) {
					CalculateCollisionFinalPosition(particle, time);
					time = 0;
				}
				render.blit_all(particle.pos.x, particle.pos.y);
				loop_counter++;
			}

		}
		char_const_acc = 'A';
		cout << endl << endl;
	}
	

	system("pause");
	return 0;
}
