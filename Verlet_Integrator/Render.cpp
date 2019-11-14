#include "Render.h"
#include "Verlet.h"
#include "p2Log.h"


ModuleRender::ModuleRender() {
	ball = nullptr;
}
ModuleRender::~ModuleRender() {}

bool ModuleRender::Render() {



	return true;
}

void ModuleRender::Init() {
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO);

	//SDL_Event event;
	//SDL_Rect rectBall;

	//rectBall.x = 100;//pos
	//rectBall.y = 100;//pos
	//rectBall.w = 100;//pos
	//rectBall.h = 100;//pos
	
	//SDL_Surface *surBall;
	//SDL_Texture *texBall;
	//IMG_Init(IMG_INIT_PNG);


	window = SDL_CreateWindow("Verlet Integrator Josep Puto AMO", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderClear(renderer);

	doraemonrect.x = 0;
	doraemonrect.y = 0;
	doraemonrect.w = 100;
	doraemonrect.h = 100;

	surfacedoraemon = IMG_Load("Assets/Doraemon.png");
	texdoraemon = SDL_CreateTextureFromSurface(renderer, surfacedoraemon);
	SDL_FreeSurface(surfacedoraemon);

	//texBall = IMG_LoadTexture(renderer, "ball");
	//
	//surBall = IMG_Load("SDL_Image/Textures");
	//texBall = SDL_CreateTextureFromSurface(renderer, surBall);
	//SDL_RenderClear(renderer);
	//SDL_RenderCopy(renderer, texBall, NULL, &rectBall);
	//SDL_FreeSurface(surBall);
}

void ModuleRender::blit_all(float x_ball, float y_ball) {
	doraemonrect.x = x_ball;
	doraemonrect.y = y_ball;
	SDL_RenderPresent(renderer);
	SDL_RenderCopy(renderer, texdoraemon, NULL, &doraemonrect);
	//SDL_Delay(30);
}