#ifndef _VERLET_H_
#define _VERLET_H_
#include <math.h>
#include "p2Point.h"

#define PI 3.1416

struct VRectangle {
	float x = 0;
	float y = 0;
	float w = 0;
	float h = 0;
	VRectangle(){};
	~VRectangle() {};
	VRectangle(float u_x, float u_y, float u_w, float u_h){
		x = u_x;
		y = u_y;
		w = u_w;
		h = u_h;
	}
};

class Verlet{
public:
	Verlet();
	~Verlet();
	bool CheckCollision(VRectangle* rect);
public:
	fPoint pos;
	fPoint next_pos;
	fPoint prev_pos;
	fPoint v;
	fPoint a;
	float density;
	float area;
	float drag_coeficient;
	float dt;
	float mass;
	int radius;
	float gravity;
};

void InitialSituation(Verlet &particle, float dt);
fPoint Verlet_Integration(fPoint pos_i, fPoint& pos_o, fPoint ai, float dt);
fPoint Classical_Motion(fPoint pos, fPoint vi, fPoint ai, float dt);
fPoint Velocity_Verlet(fPoint vi, fPoint ai, fPoint a_new, float dt);
fPoint Stormer_Verlet(fPoint pos, fPoint pos_new, fPoint a, float dt);
float Flight_Time(float vi, float gravity, float angle);
float Flight_Time(fPoint vi, float gravity);
float Time_To_Distance(float pos, float a, float dt, float distance);
float Calculate_Time(float pos_i, float pos_new, float v, float a);
fPoint Verlet_Acceleration(float m, fPoint total_f);
fPoint Calculate_Acceleration(fPoint vi, fPoint vf, float dt);
fPoint Forces_Sum(fPoint f1, fPoint f2);
fPoint DragAcceleration(float density, float drag_coefficient, float area, fPoint speed, float mass);
bool CheckCollision(Verlet particle, VRectangle rect);
float CalculateCollisionPosition(Verlet& particle, VRectangle rect);
void CalculateCollisionFinalPosition(Verlet& particle, float time);
fPoint AccelerationSum(Verlet particle);

float Module(fPoint var);


#endif // !_VERLET_H_


