#ifndef _PHYSICS_H
#define _PHYSICS_H

class Physics
{
public:
	Physics();
	~Physics();

	bool InitialSituation();
	bool Integrate();

public:
	float x;
	float x_old;
	float v;
	float a;
	float dt;
};

#endif // !_PHYSICS_H
