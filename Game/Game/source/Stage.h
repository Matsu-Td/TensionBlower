#pragma once
#include "appframe.h"

class Stage : public ObjectBase{
public:
	Stage();
	~Stage();

	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::STAGE; }

	void Initialize();
	void Terminate();
	void Process();
	void Render();

	static Stage* GetInstance() { return _pInstance; }
	static Stage* _pInstance;

};
