#ifndef __RENDER_H__
#define __RENDER_H__

#include "Module.h"
#include <limits.h>

struct SDL_Renderer;

class Render : public Module
{
public:
	Render();
	~Render();

	bool Init();
	bool PostUpdate();
	bool CleanUp();
	
};

#endif //__RENDER_H__