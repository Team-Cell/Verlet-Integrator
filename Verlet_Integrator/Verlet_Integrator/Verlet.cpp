#include <iostream>
#include "Verlet.h"
#include "p2Point.h"
using namespace std;

Verlet::Verlet() {
	pos = { 0,0 };
	prev_pos = { 0,0 };
	v = { 0,0 };
	a = { 0,0 };
	area = 1;
	density = 1;
	dt = 1;
	m = 0;
}

Verlet::~Verlet() {}

bool InitialSituation(Verlet &particle, int case_num) {
	bool ret = true;
	switch (case_num) {
	case 0: //acceleration == 0 and dt == 1, both constant
		particle.prev_pos.x = particle.pos.x - particle.v.x;
		particle.prev_pos.y = particle.pos.y - particle.v.y;
		break;
	case 1: //acceleration == 0 and dt !=||== 1, both constant
		particle.prev_pos.x = particle.pos.x - particle.v.x * particle.dt;
		particle.prev_pos.y = particle.pos.y - particle.v.y * particle.dt;
		break;
	case 2: //acceleration !=||== 0 and dt == 1, both constant
		particle.prev_pos.x = particle.pos.x - (particle.v.x - particle.a.x) - 0.5 * particle.a.x;
		particle.prev_pos.y = particle.pos.y - (particle.v.y - particle.a.y) - 0.5 * particle.a.y;
		break;
	case 3: //acceleration !=||== 0 and dt !=||== 1, both constant
		particle.prev_pos.x = particle.pos.x - (particle.v.x - particle.a.x * particle.dt) * particle.dt - 0.5 * particle.a.x * particle.dt * particle.dt;
		particle.prev_pos.y = particle.pos.y - (particle.v.y - particle.a.y * particle.dt) * particle.dt - 0.5 * particle.a.y * particle.dt * particle.dt;
		break;
	}
	particle.pos = Verlet_Integration(particle.pos, particle.prev_pos, particle.v, particle.a, particle.dt);
	return true;
}

fPoint Integration(fPoint pos, fPoint& prev_pos, fPoint ai, float dt) {

	fPoint pos_new, v_new, a_new, vi;

	pos_new = pos + (pos - prev_pos) + ai * dt * dt;

	vi = (pos_new - pos) / (2 * dt);

	v_new = vi + ai * dt;

	a_new = (v_new - vi) / dt;

	cout << "px: " << pos_new.x <<  "py: " << pos_new.y << " vx: " << v_new.x << "vy: " << v_new.y << " ax: " << a_new.x << "ay: " << a_new.y << endl;

	prev_pos = pos;

	return pos_new;
}

fPoint Verlet_Integration(fPoint pos_i, fPoint& pos_o, fPoint vi, fPoint ai, float dt) {

	fPoint pos_new, v_new, a_new;

	pos_new = pos_i + (pos_i - pos_o) + ai * dt * dt;

	v_new = vi + ai * dt;

	a_new = (v_new - vi) / dt;

	cout << "p: " << Module(pos_new) << " v: " << Module(v_new) << " a: " << Module(a_new) << endl;

	pos_o = pos_i;

	return pos_o;
}

fPoint Velocity_Verlet(fPoint vi, fPoint ai, fPoint a_new, float dt) {

	fPoint v_new;

	v_new = vi + ((ai + a_new) / 2) * dt;

	cout << " v: " << Module(v_new) << " a: " << Module(a_new) << endl;

	return v_new;
}

fPoint Velocity_Verlet(fPoint pos_i, fPoint& pos_new, fPoint vi, fPoint ai, fPoint a_new, float dt) {

	fPoint v_new;

	pos_new = pos_i + vi * dt + ai * 0.5 * dt * dt;

	v_new = vi + ((ai + a_new) / 2) * dt;

	cout << "p: " << Module(pos_new) << " v: " << Module(v_new) << " a: " << Module(a_new) << endl;

	return v_new;
}

float Flight_Time(float vi, float gravity, float angle) {

	float time;

	time = (2 * vi * sin(angle * PI / 180)) / gravity;

	return time;
}

float Flight_Time(fPoint vi, float gravity) {

	float time;

	time = (2 * vi.y) / gravity;

	return time;
}

float Time_To_Distance(float pos, float a, float dt, float distance) {
	float prev_pos = pos;
	float time = 0.0f;
	float temp_pos;

	while (pos < distance)
	{
		time += dt;
		temp_pos = pos;
		pos = 2 * pos - prev_pos + a * dt * dt;
		prev_pos = temp_pos;
	}
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

fPoint Calculate_Two_Forces(fPoint f1, fPoint f2) {
	fPoint total_f;

	total_f = f1 + f2;

	return total_f;
}

//float aerodynamic_speed(){}

//float aerodynamic_acceleration(){}

float Module(fPoint var) {

	return sqrt(var.x * var.x + var.y * var.y);

}

//This while could be used to calculate a number of forces before sending to the Verlet_Acceleration function
/*p2Point<float> Calculate_Total_Forces(int number_forces) {
	while (number_forces > 1) {
		Calculate_Two_Forces()
		number_forces--;
	}
}*/

