#include <iostream>
#include "Physics.h"
#include "Verlet.h"
#include "p2Log.h"
using namespace std;

Physics::Physics() {
	 pos = { 0,0 };
	 pos_old = { 0,0 };
	 v = { 0,0 };
	 a = { 0,0 };
	 dt = 1;
	 m = 0;
}

Physics::~Physics() {

}

bool Physics::InitialSituation(int case_num) {
	bool ret = true;
	switch (case_num) {
	case 0: //acceleration == 0 and dt == 1, both constant
		pos_old.x = pos.x - v.x;
		pos_old.y = pos.y - v.y;
		break;
	case 1: //acceleration == 0 and dt !=||== 1, both constant
		pos_old.x = pos.x - v.x * dt;
		pos_old.y = pos.y - v.y * dt;
		break;
	case 2: //acceleration !=||== 0 and dt == 1, both constant
		pos_old.x = pos.x - (v.x - a.x) - 0.5 * a.x;
		pos_old.y = pos.y - (v.y - a.y) - 0.5 * a.y;
		break;
	case 3: //acceleration !=||== 0 and dt !=||== 1, both constant
		pos_old.x = pos.x - (v.x - a.x * dt) * dt - 0.5 * a.x * dt * dt;
		pos_old.y = pos.y - (v.y - a.y * dt) * dt - 0.5 * a.y * dt * dt;
		break;
	}
	pos = Verlet_Integration(pos, pos_old, a, dt);
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
	pos = Verlet_Integration(pos, pos_old, a, dt);
	return ret;
}
