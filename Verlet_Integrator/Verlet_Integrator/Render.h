#ifndef __RENDER_H__
#define __RENDER_H__

#include "Physics.h"

class Render 
{
public:
	Render();
	~Render();
	
	bool RenderResults(Physics particle);
	
};

#endif //__RENDER_H__