#include "Verlet.h"

void main() {
	float x, x_old;
	float v;
	float a = 0;
	float dt = 1;

	cout << "Case dt: " << dt << " and a: " << a << endl;
	x_old = 0;
	x = Verlet_Integration(5, x_old, a, dt);
	while (x <=50)
	{
		x = Verlet_Integration(x, x_old, a, dt);
	}
	cout << endl;

	a = 1;
	cout << "Case dt: " << dt << " and a: " << a << endl;
	x_old = 0;
	x = Verlet_Integration(5, x_old, a, dt);
	while (x <= 50)
	{
		x = Verlet_Integration(x, x_old, a, dt);
	}
	cout <<endl;

	dt = 0.5;
	cout << "Case dt: " << dt << " and a: " << a << endl;
	x_old = 0;
	x = Verlet_Integration(5, x_old, a, dt);
	while (x <= 50)
	{
		x = Verlet_Integration(x, x_old, a, dt);
	}
}