#ifndef _VERLET_H
#define _VERLET_H
#include <iostream>
using namespace std;

float Verlet_Integration(float xi, float& xo, float ai, float dt) {

	float x_new, v_new, a_new;

	x_new = xi + (xi - xo) + ai * dt * dt;

	v_new = (x_new - xi) / dt;

	a_new = ai;

	cout << "x: " << x_new << " v: " << v_new << " a: " << a_new << endl;

	xo = xi;

	return x_new;
}

//Different variations of the same functions must be done depending on which components we have

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

float Verlet_Acceleration(float fi, float m) {
	
	float a_new;

	a_new = fi / m;

	return a_new;
}

float Verlet_Acceleration(float fi, float fi2, float m) {

	float a_new, f_total;

	f_total = fi + fi2;

	a_new = f_total / m;

	return a_new;
}

//Other functions which return different values depending on the variables we have

#endif // !_VERLET_H
