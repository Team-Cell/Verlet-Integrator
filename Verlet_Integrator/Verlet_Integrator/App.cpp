#include <iostream> 
#include <sstream> 

#include "App.h"
#include "Render.h"
#include "Physics.h"

// Constructor
Application::Application()
{
	render = new Render();
	physics = new Physics();
}

// Destructor
Application::~Application(){
	
}

bool Application::Init()
{
	bool ret = true;

	return ret;
}

bool Application::Awake()
{
	bool ret = true;

	return ret;
}

bool Application::Start()
{
	bool ret = true;
	physics->Start();
	render->Start();
	return ret;
}

bool Application::PreUpdate()
{
	bool ret = true;

	ret = physics->PreUpdate();

	return ret;
}

bool Application::Update()
{
	bool ret = true;

	if (ret == true)
		ret = PreUpdate();
	if (ret == true)
		ret = PostUpdate();
	return ret;
}

bool Application::PostUpdate()
{
	bool ret = true;

	ret = render->PostUpdate();

	return ret;
}

// Called before quitting
bool Application::CleanUp()
{
	bool ret = true;

	App->physics->CleanUp();
	App->render->CleanUp();

	return ret;
}
