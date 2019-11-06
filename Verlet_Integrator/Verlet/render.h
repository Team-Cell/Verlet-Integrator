#ifndef __RENDER_H__
#define __RENDER_H__

#include "Physics.h"
#include "SDL/include/SDL.h"

class Render
{
public:
	Render();
	~Render();
	bool InitRender();
	bool RenderResults(Physics particle);

public:
	SDL_Window* window;
	SDL_Renderer* renderer;
};

#endif //__RENDER_H__
