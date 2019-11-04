#include "Physics.h"
#include <iostream>
#include "Verlet.h"
using namespace std;

bool Physics::Awake() {
	bool ret = true;
	return ret;
}

bool Physics::Start() {
	bool ret = true;

	float x, x_old;
	float v;
	float a = 0;
	float dt = 1;

	cout << "Case dt: " << dt << " and a: " << a << endl;
	x_old = 0;
	x = Verlet_Integration(5, x_old, a, dt);
	while (x <= 50)
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
	cout << endl;

	dt = 0.5;
	cout << "Case dt: " << dt << " and a: " << a << endl;
	x_old = 0;
	x = Verlet_Integration(5, x_old, a, dt);
	while (x <= 50)
	{
		x = Verlet_Integration(x, x_old, a, dt);
	}

	return ret;
}

bool Physics::PreUpdate() {
	bool ret = true;
	return ret;
}

bool Physics::CleanUp() {
	bool ret = true;
	return ret;
}