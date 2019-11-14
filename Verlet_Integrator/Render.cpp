#include "Render.h"
#include "Verlet.h"
#include "p2Log.h"


ModuleRender::ModuleRender() {
	ball = nullptr;
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO);

	window = SDL_CreateWindow("Verlet Integrator Josep Puto AMO", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
ModuleRender::~ModuleRender() {}

bool ModuleRender::Render() {

	return true;
}

void ModuleRender::Init() {

	SDL_RenderClear(renderer);

	//// GRAPHICS BACKGROUND ////
	backgroundrect.x = 0;
	backgroundrect.y = 0;
	backgroundrect.w = SCREEN_WIDTH;
	backgroundrect.h = SCREEN_HEIGHT;
	surfacebackground = IMG_Load("Assets/Background.png");
	texbackground = SDL_CreateTextureFromSurface(renderer, surfacebackground);
	SDL_FreeSurface(surfacebackground);
	SDL_RenderCopy(renderer, texbackground, NULL, &backgroundrect);


	//// BALL GRAPHICS INIT ////
	doraemonrect.x = 0;
	doraemonrect.y = 0;
	doraemonrect.w = 27;
	doraemonrect.h = 27;
	surfacedoraemon = IMG_Load("Assets/Ball.png");
	texdoraemon = SDL_CreateTextureFromSurface(renderer, surfacedoraemon);
	SDL_FreeSurface(surfacedoraemon);
}

void ModuleRender::blit_all(float x_ball, float y_ball) {
	doraemonrect.x = x_ball;
	doraemonrect.y = y_ball;
	SDL_RenderPresent(renderer);
	SDL_RenderCopy(renderer, texdoraemon, NULL, &doraemonrect);
	//SDL_Delay(30);
}

void ModuleRender::clearScreen() {
	SDL_RenderClear(renderer);
}