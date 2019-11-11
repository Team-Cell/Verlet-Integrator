#pragma once
#ifndef __ModuleRenderer_H__
#define __ModuleRenderer_H__

#include "Verlet.h"
#include"include/SDL.h"

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
	SDL_Texture* tex;

};
#endif // !__ModuleRenderer_H__
