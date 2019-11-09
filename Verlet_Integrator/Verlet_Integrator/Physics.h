#ifndef _PHYSICS_H
#define _PHYSICS_H

class Physics
{
public:
	Physics();
	~Physics();

	bool InitialSituation(int case_num = 0);
	bool Integrate();

public:
	float x;
	float x_old;
	float v;
	float a;
	float dt;
	float m;
};

#endif // !_PHYSICS_H
