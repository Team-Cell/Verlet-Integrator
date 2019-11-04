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
bool Render::PreUpdate()
{
	bool ret = true;

	return ret;
}

bool Render::Update()
{	
	bool ret = true;

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