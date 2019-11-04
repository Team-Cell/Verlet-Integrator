#include "App.h"
#include "Render.h"

#include <cstdlib>
#include <time.h>

Render::Render() : Module()
{
}

// Destructor
Render::~Render()
{}

// Called before render is available
bool Render::Init()
{
	bool ret = true;

	return ret;
}

// Called every draw update
update_status Render::PreUpdate()
{
	update_status ret = UPDATE_CONTINUE;

	return ret;
}

update_status Render::Update()
{	
	update_status ret = UPDATE_CONTINUE;

	return ret;
}

update_status Render::PostUpdate()
{
	update_status ret = UPDATE_CONTINUE;

	return ret;
}

// Called before quitting
bool Render::CleanUp()
{
	bool ret = true;

	return ret;
}