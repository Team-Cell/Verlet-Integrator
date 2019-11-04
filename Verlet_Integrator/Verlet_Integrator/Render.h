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
	update_status PreUpdate();	
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	
};

#endif //__ModuleRenderer_H__