#ifndef _VERLET_H_
#define _VERLET_H
#include <math.h>
#include "p2Point.h"

#define PI 3.1416

class Verlet
{
public:
	Verlet();
	~Verlet();

public:
	fPoint pos;
	fPoint next_pos;
	fPoint prev_pos;
	fPoint v;
	fPoint a;
	float density;
	float area;
	float drag_coeficient;
	float dt = 1;
	float m;
};

bool InitialSituation(Verlet &particle, int case_num = 0);
fPoint Integration(fPoint pos_i, fPoint& pos_o, fPoint ai, float dt);
fPoint Verlet_Integration(fPoint pos_i, fPoint& pos_o, fPoint vi, fPoint ai, float dt);
fPoint Velocity_Verlet(fPoint vi, fPoint ai, fPoint a_new, float dt);
fPoint Velocity_Verlet(fPoint pos_i, fPoint& pos_new, fPoint vi, fPoint ai, fPoint a_new, float dt);
float Flight_Time(float vi, float gravity, float angle);
float Flight_Time(fPoint vi, float gravity);
float Time_To_Distance(float pos, float a, float dt, float distance);
fPoint Verlet_Acceleration(float m, fPoint total_f);
fPoint Calculate_Acceleration(fPoint vi, fPoint vf, float dt);
fPoint Calculate_Two_Forces(fPoint f1, fPoint f2);

float Module(fPoint var);


#endif // !_VERLET_H_


