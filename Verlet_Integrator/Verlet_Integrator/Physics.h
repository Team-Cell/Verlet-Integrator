#ifndef _PHYSICS_H
#define _PHYSICS_H
#include "Module.h"

class Physics : public Module
{
public:
	Physics(){}
	~Physics(){}

	bool Awake();

	bool Start();

	bool PreUpdate();

	bool CleanUp();

public:
	float x, x_old;
	float v;
	float a = 0;
	float dt = 1;
};

#endif // !_PHYSICS_H

