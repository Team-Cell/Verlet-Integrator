#include <iostream>
#include "Physics.h"
#include "Render.h"
using namespace std;

void main() {
	Physics particle;
	Render render;
	

	cout << "Case dt: " << particle.dt << " and a: " << particle.a << endl;
	particle.InitialSituation();

		while (particle.x <= 500) {
			particle.Integrate();
			render.RenderResults(particle);
		}
}