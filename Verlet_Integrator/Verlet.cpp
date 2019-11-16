#include <iostream>
#include "Verlet.h"
#include "Render.h"
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
	gravity = 0;
}

Verlet::~Verlet() {}

void InitialSituation(Verlet &particle, float dt) {
	bool ret = true;
	/*
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
	*/
	//a = AccelerationSum(particle) * -1;
	particle.a = AccelerationSum(particle);
	particle.prev_pos = particle.pos - particle.v * dt + particle.a * 0.5f * dt * dt;

	//particle.pos = Verlet_Integration(particle.pos, particle.prev_pos, particle.a, particle.dt);
}


//Main formulas

fPoint Verlet_Integration(fPoint pos, fPoint& prev_pos, fPoint ai, float dt) {

	fPoint pos_new;

	pos_new = pos + (pos - prev_pos) + ai * dt * dt;

	//a_new = (v_new - vi) / dt;

	cout << "px: " << pos_new.x << " py: " << SCREEN_HEIGHT - pos_new.y << " ax: " << -ai.x << " ay: " << -ai.y << endl;

	prev_pos = pos;

	return pos_new;
}

fPoint Classical_Motion(fPoint pos, fPoint vi, fPoint ai, float dt) {

	fPoint pos_new, v_new, a_new;

	pos_new = pos + vi * dt + ai * dt * dt;

	v_new = vi + ai * dt;

	a_new = (v_new - vi) / dt;

	cout << "px: " << pos_new.x << " py: " << pos_new.y << " vx: " << v_new.x << " vy: " << v_new.y << " ax: " << a_new.x << " ay: " << a_new.y << endl;

	return pos;
}

fPoint Velocity_Verlet(fPoint vi, fPoint ai, fPoint a_new, float dt) {

	fPoint v_new;

	v_new = vi + ((ai + a_new) * 0.5) * dt;

	cout << " vx: " << v_new.x << " vy: " << v_new.y << " ax: " << -a_new.x << " ay: " << -a_new.y << endl;

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
	accelerationSum.x = accelerationSum.y = 0;
	accelerationSum = particle.a;
	accelerationSum.y += particle.gravity;
	accelerationSum -= DragAcceleration(particle.density, particle.drag_coeficient, particle.area, particle.v, particle.mass);
	return accelerationSum;
}

fPoint DragAcceleration(float density, float drag_coefficient, float area, fPoint speed, float mass) {
	fPoint acceleration;
	acceleration.x = ((0.5 * density * drag_coefficient * area) * (speed.x * speed.x)) / mass;
	acceleration.y = ((0.5 * density * drag_coefficient * area) * (speed.y * speed.y)) / mass;
	return acceleration;
}

bool CheckCollision(Verlet particle, VRectangle rect) {
	bool ret = false;
	if (particle.pos.x + particle.radius >= rect.x && particle.pos.x - particle.radius <= rect.x + rect.w && particle.pos.y - particle.radius <= rect.y + rect.h && particle.pos.y + particle.radius >= rect.y) {
		ret = true;
	}

	return ret;
}


bool Verlet::CheckCollision(VRectangle* rect) {
		return (pos.x < rect->x + rect->w &&
			pos.x + radius > rect->x &&
			pos.y < rect->y + rect->h &&
			radius + pos.y > rect->y);
}

float CalculateCollisionPosition(Verlet& particle, VRectangle rect) {

	float time = 0;
	bool col_x, col_y;
	col_x = col_y = false;
	
	if (particle.prev_pos.x + particle.radius < rect.x) {
		time = Calculate_Time(particle.prev_pos.x, rect.x, particle.v.x, particle.a.x);
		col_x = true;
	}
	else if(particle.prev_pos.x - particle.radius > rect.x + rect.w) {
		time = Calculate_Time(particle.prev_pos.x, rect.x + rect.w, particle.v.x, particle.a.x);
		col_x = true;
	}
	else if (particle.prev_pos.y + particle.radius < rect.y) {
		time = Calculate_Time(particle.prev_pos.y, rect.y, particle.v.y, particle.a.y);
		col_y = true;
	}
	else if (particle.prev_pos.y - particle.radius > rect.y + rect.h) {
		time = Calculate_Time(particle.prev_pos.y, rect.y + rect.h, particle.v.y, particle.a.y);
		col_y = true;
	}

	particle.pos = particle.prev_pos + particle.v * time + particle.a * 0.5 * time * time;
	if (col_x == true) {
		particle.v.x = -particle.v.x * 0.9;
		//particle.a.x = -particle.a.x;
	}
	else if (col_y == true) {
		particle.v.y = -particle.v.y * 0.9;
		//particle.a.y = -particle.a.y;
	}
	return time;
}

void CalculateCollisionFinalPosition(Verlet& particle, float time) {
	time = particle.dt - time;
	particle.pos = particle.prev_pos + particle.v * time + particle.a * 0.5 * time * time;
	particle.prev_pos=particle.pos- particle.v * particle.dt - particle.a * 0.5 * particle.dt * particle.dt;
}


float Calculate_Time(float pos_i, float pos_new, float v, float a) {
	float time, time1, time2, t_pow;

	//v * time + a * 0.5 * time * time + pos_i - pos_new = 0;
	if (a == 0) {
		time = (pos_new - pos_i) / v;
		return time;
	}
	t_pow = pow((v * v) - ((pos_i - pos_new) * a * 2), 0.5);
	time1 = (-v + t_pow) / a;
	time2 = (-v - t_pow) / a;
	if (time1 > 0)time = time1;
	else if (time2 > 0)time = time2;
	else time = 0;

	return time;
}

//Additional formulas

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

fPoint Forces_Sum(fPoint f1, fPoint f2) {
	fPoint total_f;

	total_f = f1 + f2;

	return total_f;
}

//This while could be used to calculate a number of forces before sending to the Verlet_Acceleration function
/*p2Point<float> Calculate_Total_Forces(int number_forces) {
	while (number_forces > 1) {
		Calculate_Two_Forces()
		number_forces--;
	}
}*/

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