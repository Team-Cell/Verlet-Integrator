#ifndef _VERLET_H
#define _VERLET_H
#include <iostream>
using namespace std;

float Verlet_Integration(float xi, float& xo, float ai, float dt) {

	float x_new, v_new, a_new, vi;

	x_new = xi + (xi - xo) + ai * dt * dt;

	vi = (x_new - xo) / (2 * dt);

	v_new = vi + ai * dt;

	a_new = (v_new - vi) / dt;

	cout << "x: " << x_new << " v: " << v_new << " a: " << a_new << endl;

	xo = xi;

	return x_new;
}

//Different variations of the same functions must be done depending on which components we have

float Verlet_Integration(float xi, float& xo, float vi, float ai, float dt) {

	float x_new, v_new, a_new;

	x_new = xi + (xi - xo) + ai * dt * dt;

	v_new = vi + ai * dt;

	a_new = (v_new - vi) / dt;

	cout << "x: " << x_new << " v: " << v_new << " a: " << a_new << endl;

	xo = xi;

	return x_new;
}


// TODO 1: 
//Make a function which returns the velocity Verlet
float Verlet_Velocity(float vi, float ai, float a_new, float dt) {

	float v_new;

	v_new = vi + ((ai + a_new) / 2) * dt;

	cout << " v: " << v_new << " a: " << a_new << endl;

	return v_new;
}

float Verlet_Velocity(float xi, float& x_new, float vi, float ai, float a_new, float dt) {

	float v_new;

	x_new = xi + vi * dt + 0.5 * ai * dt * dt;

	v_new = vi + ((ai + a_new) / 2) * dt;

	cout << "x: " << x_new << " v: " << v_new << " a: " << a_new << endl;

	return v_new;
}

//TODO 2:
//Make a function which returns the acceleration 

float Verlet_Acceleration(float m, float total_f) {
	float a_new;

	a_new = total_f / m;
	
	return a_new;
}


//This while could be used to calculate a number of forces before sending to the Verlet_Acceleration function
/*float Calculate_Total_Forces(int number_forces) {
	while (number_forces > 1) {
		Calculate_Two_Forces()
		number_forces--;
	}
}*/

float Calculate_Two_Forces(float f1, float f2) {
	float total_f;

	total_f = f1 + f2;

	return total_f;
}
//Other functions which return different values depending on the variables we have

#endif // !_VERLET_H
