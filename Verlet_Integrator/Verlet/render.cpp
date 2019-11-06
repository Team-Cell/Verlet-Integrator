#include <stdlib.h>
#include "Render.h"
#include "p2Log.h"


Render::Render() {
}

Render::~Render() {}

bool Render::InitRender() {

	bool ret = true;

	LOG("Initing render");

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		window = SDL_CreateWindow("Simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
			SDL_RenderClear(renderer);
		}
	}
	return ret;
}

bool Render::RenderResults(Physics particle)
{

	bool ret = true;

	//all render functions here

	return ret;
}
