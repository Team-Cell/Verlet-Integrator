#include <iostream> 
#include <sstream> 

#include "App.h"
#include "Render.h"

// Constructor
Application::Application()
{
	render = new Render();
}

// Destructor
Application::~Application()
{
}

void Application::AddModule(Module* module)
{

}

bool Application::Init()
{
	bool ret = true;

	return ret;
}

// Called before render is available
bool Application::Awake()
{
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Application::Start()
{
	bool ret = true;

	return ret;
}

// Call modules before each loop iteration
update_status Application::PreUpdate()
{
	update_status ret = UPDATE_CONTINUE;

	return ret;
}

// Called each loop iteration
update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	return ret;
}

// Call modules after each loop iteration
update_status Application::PostUpdate()
{
	update_status ret = UPDATE_CONTINUE;

	return ret;
}

// Called before quitting
bool Application::CleanUp()
{
	bool ret = true;

	return ret;
}
