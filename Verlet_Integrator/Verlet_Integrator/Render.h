#pragma once
#ifndef __ModuleRenderer_H__
#define __ModuleRenderer_H__

#include "Verlet.h"
#include "../SDL/include/SDL.h"
#include"../SDL_image/include/SDL_image.h"

struct SDL_Renderer;
struct SDL_Texture;


class ModuleRender : public Verlet
{
public:
	ModuleRender();
	~ModuleRender();

	bool Render();
	

public:
	SDL_Renderer* renderer = nullptr;
	SDL_Rect* ball;
	SDL_Texture* tex = nullptr;

};
#endif // !__ModuleRenderer_H__
