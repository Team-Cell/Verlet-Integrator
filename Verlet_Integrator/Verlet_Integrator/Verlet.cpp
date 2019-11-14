#include <iostream>
#include "Verlet.h"
#include "p2Point.h"
#include "p2Log.h"
#include <math.h>
using namespace std;

Verlet::Verlet() {
	pos = { 0,0 };
	prev_pos = { 0,0 };
	v = { 0,0 };
	a = { 0,0 };
	area = 1;
	density = 1;
	dt = 1;
	mass = 0;
	drag_coeficient = 0;
	radius = 0;
	col_state = C_NONE;
}

Verlet::~Verlet() {}

void InitialSituation(Verlet &particle, int case_num) {
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
	particle.pos = Verlet_Integration(particle.pos, particle.prev_pos, particle.a, particle.dt);
}

fPoint Verlet_Integration(fPoint pos, fPoint& prev_pos, fPoint ai, float dt) {

	fPoint pos_new, v_new, a_new, vi;

	pos_new = pos + (pos - prev_pos) + ai * dt * dt;

	//a_new = (v_new - vi) / dt;

	cout << "px: " << pos_new.x <<  " py: " << pos_new.y << endl;

	prev_pos = pos;

	return pos_new;
}

fPoint Verlet_Integration_With_Speed(fPoint pos, fPoint& prev_pos, fPoint vi, fPoint ai, float dt) {

	fPoint pos_new, v_new, a_new;

	pos_new = pos + (pos - prev_pos) + ai * dt * dt;

	v_new = vi + ai * dt;

	a_new = (v_new - vi) / dt;

	cout << "px: " << pos_new.x << " py: " << pos_new.y << " vx: " << v_new.x << " vy: " << v_new.y << " ax: " << a_new.x << " ay: " << a_new.y << endl;

	prev_pos = pos;

	return pos;
}

fPoint Velocity_Verlet(fPoint vi, fPoint ai, fPoint a_new, float dt) {

	fPoint v_new;

	v_new = vi + ((ai + a_new) * 0.5) * dt;

	cout << " vx: " << v_new.x << " vy: " << v_new.y << " ax: " << a_new.x << " ay: " << a_new.y << endl;

	return v_new;
}

fPoint Stormer_Verlet(fPoint pos, fPoint prev_pos, fPoint a, float dt) {

	fPoint v_new, next_pos;

	next_pos = Verlet_Integration(pos, prev_pos, a, dt);

	v_new = (next_pos - pos)/dt;

	cout << "px: " << next_pos.x << " py: " << next_pos.y << " vx: " << v_new.x << " vy: " << v_new.y << endl;

	return v_new;
}

fPoint AccelerationSum(Verlet particle) {
	fPoint accelerationSum;
	//accelerationSum = Acceleration_For_Drag()
	return accelerationSum;
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

float Calculate_Time(float pos_i, float pos_new, float v, float a) {
	float time, time1, time2, t_pow;

	//v * time + a * 0.5 * time * time + pos_i - pos_new = 0;
	t_pow = pow((v * v) - ((pos_i - pos_new) * a * 2), 0.5);
	time1 = (-v + t_pow) / a;
	time2= (-v - t_pow) / a;

	if (time1 > 0)time = time1;
	else if (time2 > 0)time = time2;
	else time = 0;

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

fPoint Forces_Sum(fPoint f1, fPoint f2) {
	fPoint total_f;

	total_f = f1 + f2;

	return total_f;
}

fPoint Acceleration_For_Drag(float density, float drag_coefficient, float area, fPoint speed, float mass) {
	fPoint acceleration;
	acceleration.x = ((0.5 * density * drag_coefficient * area) * (speed.x * speed.x))/ mass;
	acceleration.y = ((0.5 * density * drag_coefficient * area) * (speed.y * speed.y)) / mass;
	return acceleration;
}

//This while could be used to calculate a number of forces before sending to the Verlet_Acceleration function
/*p2Point<float> Calculate_Total_Forces(int number_forces) {
	while (number_forces > 1) {
		Calculate_Two_Forces()
		number_forces--;
	}
}*/

bool CheckCollision(Verlet particle, VRectangle rect) {
	bool ret = false;
	particle.col_state = C_NONE;
	LOG("%f, %f, %f, %f, %f, %f, %f, %f", particle.pos.x + particle.radius, rect.x, particle.pos.x - particle.radius, rect.x + rect.w, particle.pos.y + particle.radius, rect.y, particle.pos.y - particle.radius, rect.y + rect.h);
	if (particle.pos.x + particle.radius >= rect.x && particle.pos.x - particle.radius <= rect.x + rect.w && particle.pos.y - particle.radius <= rect.y + rect.h && particle.pos.y + particle.radius >= rect.y) {
		LOG("%f, %f", particle.pos.x, particle.pos.y);
		if (particle.pos.x > particle.prev_pos.x) {
			if (particle.col_state == C_NONE)particle.col_state = C_RIGHT;
			else if (particle.col_state == C_UP)particle.col_state = C_UP_RIGHT;
			else if (particle.col_state == C_DOWN)particle.col_state = C_DOWN_RIGHT;
			ret = true;
		}
		else if (particle.pos.x < particle.prev_pos.x) {
			if (particle.col_state == C_NONE)particle.col_state = C_LEFT;
			else if (particle.col_state == C_UP)particle.col_state = C_UP_LEFT;
			else if (particle.col_state == C_DOWN)particle.col_state = C_DOWN_LEFT;
			ret = true;
		}
	//else if (particle.pos.y - particle.radius <= rect.y + rect.h && particle.pos.y + particle.radius >= rect.y) {
		if (particle.pos.y < particle.prev_pos.y) {
			if (particle.col_state == C_NONE)particle.col_state = C_UP;
			else if (particle.col_state == C_LEFT)particle.col_state = C_UP_LEFT;
			else if (particle.col_state == C_RIGHT)particle.col_state = C_UP_RIGHT;
			ret = true;
		}
		else if (particle.pos.y > particle.prev_pos.y) {
			if (particle.col_state == C_NONE)particle.col_state = C_DOWN;
			else if (particle.col_state == C_LEFT)particle.col_state = C_DOWN_LEFT;
			else if (particle.col_state == C_RIGHT)particle.col_state = C_DOWN_RIGHT;
			ret = true;
		}
	}
	if (particle.col_state != C_NONE)ret = true;

	return ret;
}

void CalculatePositionCollision(Verlet particle, VRectangle rect, VRectangle rect2 /*possibly not used*/) {
	float time1, time2 = 0, time;
	bool col_x, col_y;
	col_x = col_y = false;
	fPoint pos;

	switch (particle.col_state)
	{
	case C_DOWN:
	case C_UP:
		time1 = Calculate_Time(particle.prev_pos.y, particle.pos.y, particle.v.y, particle.a.y);
		col_y = true;
		break;
	case C_DOWN_LEFT:
	case C_DOWN_RIGHT:
	case C_UP_LEFT:
	case C_UP_RIGHT:
		time2 = Calculate_Time(particle.prev_pos.y, particle.pos.y, particle.v.y, particle.a.y);
		col_y = true;
	case C_LEFT:
	case C_RIGHT:
		time1 = Calculate_Time(particle.prev_pos.x, particle.pos.x, particle.v.x, particle.a.x);
		col_x = true;
		break;
	}
	if (time2 == 0)time = time1;
	else if (time1 > time2)time = time1;
	else time = time2;
	pos = particle.prev_pos + particle.v * time + particle.a * 0.5 * time * time;
	if (col_x == true) {
		particle.v.x = -particle.v.x * 0.9;
		particle.a.x = -particle.a.x;
	}
	if (col_y == true) {
		particle.v.y = -particle.v.y * 0.9;
		particle.a.y = -particle.a.y;
	}
}

float Module(fPoint var) {

	return sqrt(var.x * var.x + var.y * var.y);

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