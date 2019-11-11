#ifndef _VERLET_H
#define _VERLET_H
#include <iostream>
#include "Physics.h"
#include "p2Point.h"
using namespace std;

#define PI 3.1416

fPoint Verlet_Integration(fPoint pos_i, fPoint& pos_o, fPoint ai, float dt) {

	fPoint pos_new, v_new, a_new, vi;

	pos_new = pos_i + (pos_i - pos_o) + ai * dt * dt;

	vi = (pos_new - pos_o) / (2 * dt);

	v_new = vi + ai * dt;

	a_new = (v_new - vi) / dt;

	cout << "p: " << Module(pos_new) << " v: " << Module(v_new) << " a: " << Module(a_new) << endl;

	pos_o = pos_i;

	return pos_new;
}

fPoint Verlet_Integration(fPoint pos_i, fPoint& pos_o, fPoint vi, fPoint ai, float dt) {

	fPoint pos_new, v_new, a_new;

	pos_new = pos_i + (pos_i - pos_o) + ai * dt * dt;

	v_new = vi + ai * dt;

	a_new = (v_new - vi) / dt;

	cout << "p: " << Module(pos_new) << " v: " << Module(v_new) << " a: " << Module(a_new) << endl;

	pos_o = pos_i;

	return pos_new;
}

fPoint Verlet_Velocity(fPoint vi, fPoint ai, fPoint a_new, float dt) {

	fPoint v_new;

	v_new = vi + ((ai + a_new) / 2) * dt;

	cout << " v: " << Module(v_new) << " a: " << Module(a_new) << endl;

	return v_new;
}

fPoint Verlet_Velocity(fPoint pos_i, fPoint& pos_new, fPoint vi, fPoint ai, fPoint a_new, float dt) {

	fPoint v_new;

	pos_new = pos_i + vi * dt + ai * 0.5 * dt * dt;

	v_new = vi + ((ai + a_new) / 2) * dt;

	cout << "p: " << Module(pos_new) << " v: " << Module(v_new) << " a: " << Module(a_new) << endl;

	return v_new;
}

float flight_time(float vi, float gravity, float angle) {
	
	float time;

	time = (2*vi*sin(angle*PI/180)) / gravity;

	return time;
}

float flight_time(fPoint vi, float gravity) {

	float time;

	time = (2 * vi.y) / gravity;

	return time;
}

fPoint Verlet_Acceleration(float m, fPoint total_f) {
	fPoint a_new;

	a_new = total_f / m;

	return a_new;
}

fPoint Calculate_Acceleration(fPoint vi, fPoint vf, float dt) {

	fPoint af;

	af.x = (vf.x - vi.x) / dt;
	af.y = (vf.y - vi.y) / dt;

	return af;
}

//This while could be used to calculate a number of forces before sending to the Verlet_Acceleration function
/*p2Point<float> Calculate_Total_Forces(int number_forces) {
	while (number_forces > 1) {
		Calculate_Two_Forces()
		number_forces--;
	}
}*/

fPoint Calculate_Two_Forces(fPoint f1, fPoint f2) {
	fPoint total_f;

	total_f = f1 + f2;

	return total_f;
}

float aerodynamic_speed(){}

float aerodynamic_acceleration(){}

#endif // !_VERLET_H
