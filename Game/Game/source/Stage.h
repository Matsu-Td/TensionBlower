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

	static Stage* GetInstance() { return _pInstance; }
	static Stage* _pInstance;
	int _mh;
};
