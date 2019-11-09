#ifndef _VERLET_H
#define _VERLET_H
#include <iostream>
#include "p2Point.h"
using namespace std;

fPoint Verlet_Integration(fPoint pos_i, fPoint& pos_o, fPoint ai, float dt) {

	fPoint pos_new, v_new, a_new, vi;

	pos_new = pos_i + (pos_i - pos_o) + ai * dt * dt;

	vi = (pos_new - pos_o) / (2 * dt);

	v_new = vi + ai * dt;

	a_new = (v_new - vi) / dt;

	cout << "x: " << pos_new.x << " y: " << pos_new.y << " v: " << v_new.x << " , " << v_new.y << " a: " << a_new.x << " , " << a_new.y << endl;

	pos_o = pos_i;

	return pos_new;
}

//Different variations of the same functions must be done depending on which components we have

fPoint Verlet_Integration(fPoint pos_i, fPoint& pos_o, fPoint vi, fPoint ai, float dt) {

	p2Point<float> pos_new, v_new, a_new;

	pos_new = pos_i + (pos_i - pos_o) + ai * dt * dt;

	v_new = vi + ai * dt;

	a_new = (v_new - vi) / dt;

	cout << "x: " << pos_new.x << " y: " << pos_new.y << " v: " << v_new.x << " , " << v_new.y << " a: " << a_new.x << " , " << a_new.y << endl;

	pos_o = pos_i;

	return pos_new;
}


// TODO 1: 
//Make a function which returns the velocity Verlet
fPoint Verlet_Velocity(fPoint vi, fPoint ai, fPoint a_new, float dt) {

	fPoint v_new;

	v_new = vi + ((ai + a_new) / 2) * dt;

	cout << "v: " << v_new.x << " , " << v_new.y << " a: " << a_new.x << " , " << a_new.y << endl;

	return v_new;
}

fPoint Verlet_Velocity(fPoint pos_i, fPoint& pos_new, fPoint vi, fPoint ai, fPoint a_new, float dt) {

	fPoint v_new;

	pos_new = pos_i + vi * dt + ai * 0.5 * dt * dt;

	v_new = vi + ((ai + a_new) / 2) * dt;

	cout << "x: " << pos_new.x << " y: " << pos_new.y << " v: " << v_new.x << " , " << v_new.y << " a: " << a_new.x << " , " << a_new.y << endl;

	return v_new;
}

//TODO 2:
//Make a function which returns the acceleration 

fPoint Verlet_Acceleration(float m, fPoint total_f) {
	p2Point<float> a_new;

	a_new = total_f / m;
	
	return a_new;
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
//Other functions which return different values depending on the variables we have

#endif // !_VERLET_H
