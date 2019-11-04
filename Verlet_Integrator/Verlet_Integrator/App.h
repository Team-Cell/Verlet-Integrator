#ifndef __j1APP_H__
#define __j1APP_H__

#include "Module.h"

#define NUM_MODULES 

//Modulers
class Render;

class Application
{
public:
	Render* render = nullptr;

public:

	// Constructor
	Application();

	// Destructor
	virtual ~Application();

	bool Init();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Call modules before each loop iteration
	update_status PreUpdate();

	// Called each loop iteration
	update_status Update();

	// Call modules after each loop iteration
	update_status PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Add a new module to handle
	void AddModule(Module* module);

};

extern Application* App;

#endif