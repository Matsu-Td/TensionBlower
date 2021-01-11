#pragma once

#include "appframe.h"
#include <list>

class BulletBase {
public:
	BulletBase();
	~BulletBase();
	virtual void Update();
	virtual void Render();

	void SetPosition(VECTOR vPos) { _vPos = vPos; }
	VECTOR GetPos() { return _vPos; }

protected:
	int _mh;
	VECTOR _vPos;
	VECTOR _scrnPos;
	float _vx, _vz;
	int _shotCnt;
	float _angle;
	float _r;
};