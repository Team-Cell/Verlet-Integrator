#include <iostream>
#include <math.h>
#include "Physics.h"
#include "Verlet.h"
#include "p2Log.h"
using namespace std;

Physics::Physics() {
	 pos = { 0,0 };
	 prev_pos = { 0,0 };
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
		prev_pos.x = pos.x - v.x;
		prev_pos.y = pos.y - v.y;
		break;
	case 1: //acceleration == 0 and dt !=||== 1, both constant
		prev_pos.x = pos.x - v.x * dt;
		prev_pos.y = pos.y - v.y * dt;
		break;
	case 2: //acceleration !=||== 0 and dt == 1, both constant
		prev_pos.x = pos.x - (v.x - a.x) - 0.5 * a.x;
		prev_pos.y = pos.y - (v.y - a.y) - 0.5 * a.y;
		break;
	case 3: //acceleration !=||== 0 and dt !=||== 1, both constant
		prev_pos.x = pos.x - (v.x - a.x * dt) * dt - 0.5 * a.x * dt * dt;
		prev_pos.y = pos.y - (v.y - a.y * dt) * dt - 0.5 * a.y * dt * dt;
		break;
	}
	pos = Verlet_Integration(pos, prev_pos, a, dt);
	return true;
}


bool Physics::Integrate(int constant_acceleration) {
	bool ret = true;

	pos = Verlet_Integration(pos, prev_pos, a, dt);

	return ret;
}

float Module(fPoint var) {

	return sqrt(var.x * var.x + var.y * var.y);

}