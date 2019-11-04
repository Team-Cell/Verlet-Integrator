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

	void Init()
	{
		active = true;
	}

	virtual bool Awake()
	{
		return true;
	}

	virtual bool Start()
	{
		return true;
	}

	virtual bool PreUpdate()
	{
		return true;
	}

	virtual bool Update()
	{
		return true;
	}

	virtual bool PostUpdate()
	{
		return true;
	}

	virtual bool CleanUp()
	{
		return true;
	}

public:

	bool	active;

};

#endif // __MODULE_H__