#pragma once

#include "appframe.h"
#include <list>

class BulletBase {
public:
	BulletBase();
	~BulletBase();
	virtual void Update();
	virtual void Render();

	void SetVecPos(VECTOR vPos) { _vPos = vPos; }
	void SetFPos(float vPosX, float vPosY, float vPosZ)
	{
		_vPos.x = vPosX;
		_vPos.y = vPosY;
		_vPos.z = vPosZ;
	}

	VECTOR GetPos() const { return _vPos; }

protected:
	int _mh;
	VECTOR _vPos;
	VECTOR _scrnPos;
	float _vx, _vz;
	int _shotCnt;
	float _angle;
	float _r;
};