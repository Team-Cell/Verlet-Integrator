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
	float x = 0;
	float x_old = 0;
	float v = 0;
	float a = 0;
	float dt = 1;
};

#endif // !_PHYSICS_H

