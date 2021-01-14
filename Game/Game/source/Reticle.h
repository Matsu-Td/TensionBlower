#pragma once
#include "appframe.h"

class Reticle : public ObjectBase{
public:
	Reticle();
	~Reticle();

	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::RETICLE; }

	void Initialize();
	void Process();
	void Render();

protected:

};
