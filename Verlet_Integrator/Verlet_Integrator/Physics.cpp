#include <iostream>
#include "Physics.h"
#include "Verlet.h"
#include "p2Log.h"
using namespace std;

Physics::Physics() {
}

Physics::~Physics() {

}

bool Physics::InitialSituation() {
	bool ret = true;
	x_old = x - v;
	x = Verlet_Integration(x, x_old, a, dt);
	return true;
}


bool Physics::Integrate() {
	bool ret = true;
	/*
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
	*/
	x = Verlet_Integration(x, x_old, a, dt);

	return ret;
}

//Different variations of the same functions must be done depending on which components we have

// TODO 1: 
//Make a function which returns the velocity Verlet

//TODO 2:
//Make a function which returns the acceleration 