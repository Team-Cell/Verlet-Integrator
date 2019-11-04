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

private:
	 
};

#endif // !_PHYSICS_H

