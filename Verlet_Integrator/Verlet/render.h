#ifndef __RENDER_H__
#define __RENDER_H__

#include "Physics.h"
#include "SDL/include/SDL.h"

class Render
{
public:
	Render();
	~Render();
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool RenderResults(Physics particle);


};

#endif //__RENDER_H__
