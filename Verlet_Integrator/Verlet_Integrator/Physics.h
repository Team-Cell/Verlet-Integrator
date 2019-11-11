#ifndef _PHYSICS_H
#define _PHYSICS_H

#include "p2Point.h"

class Physics
{
public:
	Physics();
	~Physics();

	bool InitialSituation(int case_num = 0);
	bool Integrate();

public:
	fPoint pos;
	fPoint prev_pos;
	fPoint v;
	fPoint a;
	float density;
	float area;
	float drag_coeficient;
	float dt = 1;
	float m;
};

float Module(fPoint var);

#endif // !_PHYSICS_H
