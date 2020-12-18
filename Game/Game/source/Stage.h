#pragma once

#include "appframe.h"

class Stage
{
public:
	Stage();
	~Stage();
	void Initialize();
	void Terminate();
	void Process();
	void Render();

private:
	int _mh;
};
