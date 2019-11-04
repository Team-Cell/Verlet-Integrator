#ifndef __APP_H__
#define __APP_H__

#include "Module.h"

#define NUM_MODULES 

//Modules
class Render;
class Physics;

class Application
{
public:
	Render* render = nullptr;
	Physics* physics = nullptr;

public:

	Application();

	virtual ~Application();

	bool Init();

	bool Awake();

	bool Start();

	bool PreUpdate();

	bool Update();

	bool PostUpdate();

	bool CleanUp();

};

extern Application* App;

#endif