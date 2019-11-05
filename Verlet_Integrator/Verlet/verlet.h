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

#endif // !_VERLET_H


