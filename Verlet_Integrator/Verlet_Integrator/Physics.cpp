#include <iostream>
#include "Physics.h"
#include "Verlet.h"
#include "p2Log.h"
using namespace std;

Physics::Physics() {
	 x = 0;
	 x_old = 0;
	 v = 0;
	 a = 0;
	 dt = 1;
}

Physics::~Physics() {

}

bool Physics::InitialSituation(int case_num) {
	bool ret = true;
	switch (case_num) {
	case 0: //acceleration == 0 and dt == 1, both constant
		x_old = x - v * dt;
		break;
	case 1: //acceleration == 0 and dt !=||== 1, both constant
		x_old = x - v * dt;
		break;
	case 2: //acceleration !=||== 0 and dt == 1, both constant
		x_old = x - (v - a) - 0.5 * a;
		break;
	case 3: //acceleration !=||== 0 and dt !=||== 1, both constant
		x_old = x - (v - a * dt) * dt - 0.5 * a * dt * dt;
		break;
	}
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
