#include "Render.h"
#include "Verlet.h"
#include "include/SDL.h"
#include "include/SDL.h"
#include"include/SDL_image.h"

ModuleRender::ModuleRender() {

}
ModuleRender::~ModuleRender() {

}

bool ModuleRender::Render() {
	
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO);
	SDL_Window *window;
	SDL_Renderer *renderer;
	
	SDL_Event event;
	SDL_Rect rectBall;

	rectBall.x = 100;//pos
	rectBall.y = 100;//pos
	rectBall.w = 100;//pos
	rectBall.h = 100;//pos
	
	SDL_Surface *surBall;
	SDL_Texture *texBall;
	IMG_Init(IMG_INIT_PNG);
	window = SDL_CreateWindow("Verlet Integrator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	texBall = IMG_LoadTexture(renderer, "ball");

	surBall = IMG_Load("SDL_Image/Textures");
	texBall = SDL_CreateTextureFromSurface(renderer , surBall);
	SDL_RenderClear( renderer);
	SDL_RenderCopy( renderer, texBall , NULL , &rectBall);
	SDL_FreeSurface(surBall);



	



}
