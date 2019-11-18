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

//initial situation of the particle

void InitialSituation(Verlet &particle, float dt) {
	bool ret = true;
	//a = AccelerationSum(particle) * -1;
	particle.a = AccelerationSum(particle);
	particle.prev_pos.x = particle.pos.x - particle.v.x * dt + particle.a.x * 0.5f * dt * dt;
	particle.prev_pos.y = particle.pos.y - particle.v.y * dt + particle.a.y * 0.5f * dt * dt;

	//particle.pos = Verlet_Integration(particle.pos, particle.prev_pos, particle.a, particle.dt);
}

//main verlet

fPoint Verlet_Integration(fPoint pos, fPoint& prev_pos, fPoint ai, float dt) {

	fPoint pos_new;

	pos_new = pos + (pos - prev_pos) + ai * dt * dt;

	//a_new = (v_new - vi) / dt;

	cout << "px: " << pos_new.x << " py: " << pos_new.y << " ax: " << ai.x << " ay: " << ai.y << endl;

	prev_pos = pos;

	return pos_new;
}

fPoint Velocity_Verlet(fPoint vi, fPoint ai, fPoint a_new, float dt) {

	fPoint v_new;

	v_new = vi + ((ai + a_new) * 0.5) * dt;

	cout << " vx: " << v_new.x << " vy: " << v_new.y << " ax: " << a_new.x << " ay: " << -a_new.y << endl;

	return v_new;
}

fPoint Stormer_Verlet(fPoint pos, fPoint prev_pos, fPoint a, float dt) {

	fPoint v_new, next_pos;

	next_pos = Verlet_Integration(pos, prev_pos, a, dt);

	v_new = (next_pos - pos) / dt;

	cout << "px: " << next_pos.x << " py: " << next_pos.y << " vx: " << v_new.x << " vy: " << v_new.y << endl;

	return v_new;
}

fPoint Verlet_Acceleration(float m, fPoint total_f) {
	fPoint a_new;

	a_new = total_f / m;

	return a_new;
}

//collision related

bool CheckCollision(Verlet particle, VRectangle rect) {
	bool ret = false;
	if (particle.pos.x + particle.radius >= rect.x && 
		particle.pos.x - particle.radius <= rect.x + rect.w 
		&& particle.pos.y - particle.radius <= rect.y + rect.h 
		&& particle.pos.y + particle.radius >= rect.y) {
		ret = true;
	}
	return ret;
}

void SolveCollision(Verlet particle, VRectangle rect)
{
	float time = 0;
	fPoint aux_pos;
	fPoint a = particle.a * -1;
	aux_pos = particle.prev_pos;
	particle.prev_pos = particle.pos;
	particle.pos = aux_pos;
	while (CheckCollision(particle, rect))
	{
		particle.pos = Verlet_Integration(particle.pos, particle.prev_pos, a, 0.1);
	}
	aux_pos = particle.prev_pos;
	particle.prev_pos = particle.pos;
	particle.pos = aux_pos;
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

float CalculateCollisionPosition(Verlet& particle, VRectangle rect) {

	float time = 0;
	bool col_x, col_y;
	col_x = col_y = false;

	if (particle.prev_pos.x + particle.radius < rect.x) {
		time = Calculate_Time(particle.prev_pos.x, rect.x - particle.radius, particle.v.x, particle.a.x);
		col_x = true;
	}
	else if (particle.prev_pos.x - particle.radius > rect.x + rect.w) {
		time = Calculate_Time(particle.prev_pos.x, rect.x + rect.w + particle.radius, particle.v.x, particle.a.x);
		col_x = true;
	}
	else if (particle.prev_pos.y + particle.radius < rect.y) {
		time = Calculate_Time(particle.prev_pos.y, rect.y - particle.radius, particle.v.y, particle.a.y);
		col_y = true;
	}
	else if (particle.prev_pos.y - particle.radius > rect.y + rect.h) {
		time = Calculate_Time(particle.prev_pos.y, rect.y + rect.h + particle.radius, particle.v.y, particle.a.y);
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
	particle.pos = particle.prev_pos + particle.v * time + particle.a * 0.5 * (time * time);
	particle.prev_pos = particle.pos - particle.v * particle.dt - particle.a * 0.5 * particle.dt * particle.dt;
}

//acceleration and velocity

fPoint DragAcceleration(float density, float drag_coefficient, float area, fPoint speed, float mass) {
	fPoint acceleration;
	acceleration.x = ((0.5 * density * drag_coefficient * area) * (speed.x * speed.x)) / mass;
	acceleration.y = ((0.5 * density * drag_coefficient * area) * (speed.y * speed.y)) / mass;
	return acceleration;
}

fPoint Calculate_Acceleration(fPoint vi, fPoint vf, float dt) {

	fPoint af;

	af.x = (vf.x - vi.x) / dt;
	af.y = (vf.y - vi.y) / dt;

	return af;
}

fPoint AccelerationSum(Verlet particle) {
	fPoint accelerationSum;
	//accelerationSum.x = accelerationSum.y = 0;
	accelerationSum = particle.a;
	//accelerationSum += DragAcceleration(particle.density, particle.drag_coeficient, particle.area, particle.v, particle.mass);
	return accelerationSum;
}

float Terminal_Velocity(Verlet particle) {
	return sqrt((2 * particle.mass * particle.gravity) / (particle.density * particle.drag_coeficient * particle.area));
}

//position calculators

float Time_To_Position(fPoint initial_position, fPoint acceleration, float dt, fPoint final_position) {
	float time = 0;
	Verlet particle;
	particle.prev_pos = initial_position;
	particle.a = acceleration;
	int max_iterations = 100;
	int current_iterations = 0;
	LOG("here");
	InitialSituation(particle, dt);

	while (particle.pos != final_position)
	{
		if (current_iterations > max_iterations) {
			cout << "The particle can't reach this position" << endl;
			break;
		}
		else
		{
			particle.pos = Verlet_Integration(particle.pos, particle.prev_pos, particle.a, dt);
			current_iterations++;
		}
	}
	return time;
}

fPoint Position_at_Time(fPoint pos, fPoint prev_pos, fPoint a, float time) {

	float time_passed = 0;
	float dt = 1.0f;
	while (time_passed < time)
	{
		pos = Verlet_Integration(pos, prev_pos, a, dt);
		time_passed += dt;
	}

	//cout << "px: " << pos.x << " py: " << pos.y << "ax: "<< a.x << " ay: " << a.y << endl;

	return pos;
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

//additional formulas

fPoint Forces_Sum(fPoint f1, fPoint f2) {
	fPoint total_f;

	total_f = f1 + f2;

	return total_f;
}

float Module(fPoint var) {

	return sqrt(var.x * var.x + var.y * var.y);

}

float Parachutist_Acceleration(float m, float v_y, float gravity, float k) {
	float acceleration;

	// k: constant based on falling object form

	acceleration = (-m * gravity + k * v_y * v_y) / m;

	return acceleration;
}

float Freefall_Speed(float gravity, float m, float air_density, float area, float friction_const) {
	float speed;

	speed = sqrt((2 * m * gravity) / (air_density * area * friction_const));

	return speed;
}

float Freefall_Acceleration(float gravity, float m, float friction_const) {
	float acceleration;

	acceleration = (m * gravity - m * gravity * friction_const) / m;

	return acceleration;
}

//This while could be used to calculate a number of forces before sending to the Verlet_Acceleration function
/*p2Point<float> Calculate_Total_Forces(int number_forces) {
	while (number_forces > 1) {
		Calculate_Two_Forces()
		number_forces--;
	}
}*/
