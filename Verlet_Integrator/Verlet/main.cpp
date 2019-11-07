#include <iostream>
#include <stdlib.h>
#include "Physics.h"
#include "Render.h"
#include "p2Log.h"
using namespace std;

#include "SDL/include/SDL.h"
#pragma comment(lib,"SDL/libx86/SDL2.lib")
#pragma comment(lib,"SDL/libx86/SDL2main.lib")

int main(int argc, char* args[]) {

	LOG("Starting Integrator");

	Physics particle;
	Render render;

	int firstopcionmenu = 0;

	render.InitRender();

	while ((firstopcionmenu != 2) && (firstopcionmenu >= 3 || firstopcionmenu <= 0)) {
		cout << "MENU" << endl;
		cout << "What do you want to do?" << endl << "1- Execute the program" << endl << "2- Quit" << endl;
		cin >> firstopcionmenu;
		system("cls");
		if (firstopcionmenu == 1) {
			cout << "Which is the initial speed?:" << endl;
			cin >> particle.v;
			cout << "Which is the initial position?:" << endl;
			cin >> particle.x;
			cout << "Which is the initial acceleration?: " << endl;
			cin >> particle.a;
			cout << "Which is the time difference?: " << endl;
			cin >> particle.dt;
			//system("cls");
			cout << "Case dt: " << particle.dt << " and a: " << particle.a << endl;
			particle.InitialSituation();
			while (particle.x <= 500) {
				particle.Integrate();
				render.RenderResults(particle);
			}
		}
	}
	return 0;
}
