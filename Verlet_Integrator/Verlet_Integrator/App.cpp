#include <iostream> 
#include <sstream> 

#include "App.h"
#include "Render.h"

// Constructor
App::App()
{
	render = new Render();
}

// Destructor
App::~App()
{
}

void App::AddModule(Module* module)
{

}

// Called before render is available
bool App::Awake()
{
	bool ret = true;

	return ret;
}

// Called before the first frame
bool App::Start()
{
	bool ret = true;

	return ret;
}

// Call modules before each loop iteration
bool App::PreUpdate()
{
	bool ret = true;

	return ret;
}

// Called each loop iteration
bool App::Update()
{
	bool ret = true;

	return ret;
}

// Call modules after each loop iteration
bool App::PostUpdate()
{
	bool ret = true;

	return ret;
}

// Called before quitting
bool App::CleanUp()
{
	bool ret = true;

	return ret;
}
