#include <iostream>
#include <stdlib.h>
#include "Verlet.h"
#include "Render.h"
#include "p2Log.h"
#include "SDL/include/SDL.h"
#include "SDL_Image/include/SDL_image.h"
using namespace std;

#pragma comment(lib, "SDL_Image/libx86/SDL2_image.lib")
#pragma comment(lib, "SDL/libx86/SDL2.lib")
#pragma comment(lib, "SDL/libx86/SDL2main.lib")

void request_data(Verlet& particle, int menu_option);

int main(int argc, char* args[]) {

	LOG("Starting Integrator");

	int loop_counter = 0;
	int max_loops = 40;
	fPoint temp_pos;
	int exit = 0;

	Verlet particle;
	ModuleRender render;
	int menu_option = 0;
	float dt = 1.0f;
	float time = 0;
	SDL_Event event;
	//screen limit rectangles
	VRectangle rectangles[4];
	int rectangle_thickness = 200;
	VRectangle top_rectangle(0, -SCREEN_HEIGHT, SCREEN_WIDTH, rectangle_thickness);
	VRectangle left_rectangle(-rectangle_thickness, 0, rectangle_thickness,SCREEN_HEIGHT);
	VRectangle right_rectangle(SCREEN_WIDTH, 0, rectangle_thickness, SCREEN_HEIGHT);
	VRectangle bottom_rectangle(0, SCREEN_HEIGHT, SCREEN_WIDTH, rectangle_thickness);
	rectangles[0] = top_rectangle;
	rectangles[1] = left_rectangle;
	rectangles[2] = right_rectangle;
	rectangles[3] = bottom_rectangle;

	render.Init();
	render.blit_all(0, 0);

	//menu loop
	while ((menu_option != 4) && (menu_option <= 4 || menu_option >= 0)) {
		render.Init();
		//menu
		cout << "MENU" << endl;
		cout << "What do you want to do?" << endl;
		cout << "1. Calculate specific values" << endl;
		cout << "2. Do a graphical representation of the position" << endl;
		cout << "3. Simulate in real time" << endl;
		cout << "4. Quit" << endl;
		cin >> menu_option;
		system("cls");
		switch (menu_option)
		{
		case 1:
			request_data(particle, 1);
			break;
		case 2:
			request_data(particle, 2);
			cout << "Case dt: " << particle.dt << " and a: " << particle.a.x << ", " << -particle.a.y << endl;
			particle.prev_pos = particle.pos;
			particle.pos = Classical_Motion(particle.pos, particle.v, particle.a, dt);

			//main loop
			while (loop_counter < max_loops) {
				particle.a = AccelerationSum(particle);
				temp_pos = particle.pos;
				particle.pos = Verlet_Integration(particle.pos, particle.prev_pos, particle.a, dt);
				cout << "px: " << particle.pos.x << " py: " << SCREEN_HEIGHT - particle.pos.y << " ax: " << particle.a.x << " ay: " << -particle.a.y << endl;
				particle.prev_pos = temp_pos;
				for (int i = 0; i < 4; i++)
				{
					if (CheckCollision(particle, rectangles[i])) {
						cout << "Collision" << endl;
						time += CalculateCollisionPosition(particle, rectangles[i]);
					}
				}
				if (time > 0)
				{
					CalculateCollisionFinalPosition(particle, time);
					time = 0;
				}
				render.blit_all(particle.pos.x, particle.pos.y);
				loop_counter++;

			}
			break;
		case 3:
			//simulation loop
			request_data(particle, 3);
			particle.prev_pos = particle.pos;
			particle.pos = Classical_Motion(particle.pos, particle.v, particle.a, dt);
			
			while (exit = 0) {
				while (SDL_PollEvent(&event)) {
					switch (event.type) {
					case SDL_QUIT:
						exit = 1;
						break;
					case SDL_KEYDOWN:
						if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
							exit = 1;
							break;
						}
					}
				}
			while (1)
			{
				particle.a = AccelerationSum(particle);
				particle.pos = Verlet_Integration(particle.pos, particle.prev_pos, particle.a, dt);
				for (int i = 0; i < 4; i++)
				{
					if (CheckCollision(particle, rectangles[i])) {
						cout << "Collision" << endl;
						time += CalculateCollisionPosition(particle, rectangles[i]);
					}
				}
				if (time > 0)
				{
					CalculateCollisionFinalPosition(particle, time);
					time = 0;
				}
				render.Update(particle.pos);
			}
		}
			//render particle position
			break;
		case 4:
			goto END;
			break;
		default:
			break;
		}
		//char_const_acc = 'A';
		cout << endl << endl;
	}

	END: system("pause");
	return 0;
}

void request_data(Verlet& particle, int menu_option) {
	float time = 0;
	float dt = 0.1;
	float final_position;
	char axis;
	int axis_option = 0;

	LOOP: if (menu_option == 1)
	{
		int choice = 0;
		cout << "What do you want to calculate?" << endl;
		cout << "1. Position at a certain time" << endl;
		cout << "2. Time to reach a certain position" << endl;
		cout << "3. Terminal velocity of the particle" << endl;
		cin >> choice;
		system("cls");
		switch (choice)
		{
		case 1:
			cout << "Which is the position of the particle? " << endl << "x: ";
			cin >> particle.pos.x;
			cout << "y: ";
			cin >> particle.pos.y;
			cout << "Which is the initial speed of the particle?" << endl << "x: ";
			cin >> particle.v.x;
			cout << "y: ";
			cin >> particle.v.y;
			cout << "Which is the acceleration?" << endl << "x: ";
			cin >> particle.a.x;
			cout << "y: ";
			cin >> particle.a.y;
			cout << "At which time do you want to know the position?" << endl;
			cin >> time;
			//particle.prev_pos = particle.pos;
			particle.pos = Position_at_Time(particle.pos, particle.v, particle.a, time);
			cout << "Final position: (" << particle.pos.x << ", " << particle.pos.y << ")" << endl;
			system("pause");
			break;
		case 2: 
			cout << "Which is the position of the particle?" << endl << "x: ";
			cin >> particle.pos.x;
			cout << "y: ";
			cin >> particle.pos.y;
			cout << "Which is the initial speed of the particle?" << endl << "x: ";
			cin >> particle.v.x;
			cout << "y: ";
			cin >> particle.v.y;
			cout << "Which is the acceleration of the particle?" << endl << "x: ";
			cin >> particle.a.x;
			cout << "y: ";
			cin >> particle.a.y;
			// We ask which axis and which is the final position, and it returns us the time to reach that position
			cout << "On which axis is the position? <x> or <y>";
			cin >> axis;
			if (axis == 'x')axis_option = 1;
			if (axis == 'y')axis_option = 2;
			cout << "Which is the final position in that axis?"<< endl;
			cin >> final_position;
			cout << "Time: " << Time_To_Position(particle.pos, particle.v,particle.a,dt,final_position, axis_option) << endl;
			system("pause");
			break;
		case 3:
			//ask for values
			cout << "Which is the value of the gravity?" << endl;
			cin >> particle.gravity;
			cout << "Which is mass of the particle?" << endl;
			cin >> particle.mass;
			cout << "Which is the density of the air? " << endl;
			cin >> particle.density;
			cout << "Which is the area of the particle?" << endl;
			cin >> particle.area;
			cout << "Which is the drag coeficient of the air? " << endl;
			cin >> particle.drag_coeficient;
			cout << "Terminal velocity: " << Freefall_Speed(particle.gravity,particle.mass,particle.density,particle.area,particle.drag_coeficient) << endl;
			system("pause");
			break;
		default:
			goto LOOP;
			break;
		}
		system("cls");
	}else if (menu_option == 2)
	{
		char char_const_acc = 'A';
		cout << "Which is the initial position?:" << endl << "x: ";
		cin >> particle.pos.x;
		cout << "y: ";
		cin >> particle.pos.y;
		particle.pos.y = SCREEN_HEIGHT - particle.pos.y;
		cout << "Which is the initial speed?:" << endl << "x: ";
		cin >> particle.v.x;
		cout << "y: ";
		cin >> particle.v.y;
		particle.v.y = -particle.v.y;
		while ((char_const_acc != 'y') && (char_const_acc != 'Y') && (char_const_acc != 'n') && (char_const_acc != 'N')) {
			cout << "Do you want gravity to be the only acceleration?: " << endl << "(Yes: Y / No: N)" << endl;
			cin >> char_const_acc;
			if ((char_const_acc == 'y') || (char_const_acc == 'Y')) {
				//cout << "Which is the initial acceleration?: " << endl;
				//cin >> particle.a.x >> particle.a.y;
				//particle.a.y = -particle.a.y;
				cout << "Which is the gravity?" << endl;
				cin >> particle.gravity;
				particle.gravity = -particle.gravity;
				particle.a.y = particle.gravity;
			}
			if ((char_const_acc == 'n') || (char_const_acc == 'N')) {
				cout << "Which is the gravity?" << endl;
				cin >> particle.gravity;
				particle.gravity = -particle.gravity;
				cout << "Which is the aerodynamic drag coeficient?: " << endl;
				cin >> particle.drag_coeficient;
				cout << "Which is the density of the air?: " << endl;
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
	}else if (menu_option == 3) {
		char char_const_acc = 'A';
		cout << "Which is the initial position?:" << endl << "x: ";
		cin >> particle.pos.x;
		cout << "y: ";
		cin >> particle.pos.y;
		particle.pos.y = SCREEN_HEIGHT - particle.pos.y;
		cout << "Which is the initial speed?:" << endl << "x: ";
		cin >> particle.v.x;
		cout << "y: "; 
		cin >> particle.v.y;
		particle.v.y = -particle.v.y;
		while ((char_const_acc != 'y') && (char_const_acc != 'Y') && (char_const_acc != 'n') && (char_const_acc != 'N')) {
			cout << "Do you want gravity to be the only acceleration?: " << endl << "(Yes: Y / No: N)" << endl;
			cin >> char_const_acc;
			if ((char_const_acc == 'y') || (char_const_acc == 'Y')) {
				//cout << "Which is the initial acceleration?: " << endl;
				//cin >> particle.a.x >> particle.a.y;
				//particle.a.y = -particle.a.y;
				cout << "Which is the gravity?" << endl;
				cin >> particle.gravity;
				particle.gravity = -particle.gravity;
				particle.a.y = particle.gravity;
			}
			if ((char_const_acc == 'n') || (char_const_acc == 'N')) {
				cout << "Which is the gravity?" << endl;
				cin >> particle.gravity;
				particle.gravity = -particle.gravity;
				cout << "Which is the aerodynamic drag coeficient?: " << endl;
				cin >> particle.drag_coeficient;
				cout << "Which is the density of the air?: " << endl;
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
	}
}