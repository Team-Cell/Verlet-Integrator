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
		cout << "Qué prefieres hacer?" << endl << "1- Ejecutar el programa." << endl << "2- Salir" << endl;
		cin >> firstopcionmenu;
		system("cls");
		if (firstopcionmenu == 1) {
			cout << "Introduce la velocidad inicial del objeto:" << endl;
			cin >> particle.v;
			cout << "Introduce la posicion inicial del objeto:" << endl;
			cin >> particle.x;
			cout << "Introduce la acceleracion del objeto:" << endl;
			cin >> particle.a;
			cout << "Introduce el diferencial de tiempo:" << endl;
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
