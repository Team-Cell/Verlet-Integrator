#ifndef __j1APP_H__
#define __j1APP_H__

#include "Module.h"

#define NUM_MODULES 

//Modulers
class Render;

class App
{
public:
	Render* render = nullptr;

public:

	// Constructor
	App();

	// Destructor
	virtual ~App();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Call modules before each loop iteration
	bool PreUpdate();

	// Called each loop iteration
	bool Update();

	// Call modules after each loop iteration
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Add a new module to handle
	void AddModule(Module* module);

};

extern App* App;

#endif