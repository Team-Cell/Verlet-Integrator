#ifndef __ModuleRenderer_H__
#define __ModuleRenderer_H__

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
	bool Update();
	bool PreUpdate();
	bool CleanUp();
	
};

#endif //__ModuleRenderer_H__