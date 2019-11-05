#include "Render.h"

Render::Render() {
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		window = SDL_CreateWindow("Simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
			SDL_RenderClear(renderer);
		}


	}


}

Render::~Render() {}

bool Render::RenderResults(Physics particle)
{
	
		bool ret = true;

	//all render functions here
	
	
	

	return ret;
}
