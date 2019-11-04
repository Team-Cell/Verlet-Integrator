#include "App.h"
#include "Render.h"

#include <cstdlib>
#include <time.h>

Render::Render() : Module(){}

Render::~Render()
{}

bool Render::Start()
{
	bool ret = true;
	LOG("Render started")
	return ret;
}

bool Render::PostUpdate()
{
	bool ret = true;

	return ret;
}

// Called before quitting
bool Render::CleanUp()
{
	bool ret = true;

	return ret;
}