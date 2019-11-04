#ifndef __MODULE_H__
#define __MODULE_H__

#include "Globals.h"

class App;

class Module
{
private:
	bool enabled = true;
public:

	Module() : active(false)
	{}

	virtual bool Init()
	{
		active = true;
		return true;
	}

	// Called before render is available
	virtual bool Awake()
	{
		return true;
	}

	// Called before the first frame
	virtual bool Start()
	{
		return true;
	}

	// Called each loop iteration
	virtual update_status PreUpdate()
	{
		return update_status::UPDATE_CONTINUE;
	}

	// Called each loop iteration
	virtual update_status Update(float dt)
	{
		return update_status::UPDATE_CONTINUE;
	}

	// Called each loop iteration
	virtual update_status PostUpdate()
	{
		return update_status::UPDATE_CONTINUE;
	}

	// Called before quitting
	virtual bool CleanUp()
	{
		return true;
	}

	bool IsEnabled() const { return enabled; }

	void Enable()
	{
		if (enabled == false)
		{
			enabled = true;
			Start();
		}
	}
	void Disable()
	{
		if (enabled == true)
		{
			enabled = false;
			CleanUp();
		}
	}

public:
	bool		active;

};

#endif // __MODULE_H__