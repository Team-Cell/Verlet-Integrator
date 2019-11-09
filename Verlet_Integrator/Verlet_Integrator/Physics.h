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
	fPoint pos_old;
	fPoint v;
	fPoint a;
	float dt;
	float m;
};

#endif // !_PHYSICS_H
