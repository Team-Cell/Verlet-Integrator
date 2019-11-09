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
	p2Point<float> pos;
	p2Point<float> pos_old;
	p2Point<float> v;
	p2Point<float> a;
	float dt;
	float m;
};

float Module(fPoint var);

#endif // !_PHYSICS_H
