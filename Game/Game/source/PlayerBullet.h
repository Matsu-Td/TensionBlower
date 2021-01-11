#pragma once
#include "appframe.h"
#include "BulletBase.h"

class PlayerBullet : public BulletBase{
public:
	PlayerBullet();
	~PlayerBullet();

	void Initialize();
	void Update();
	void Render();

private:
//	int    _mh;           // ���f���n���h��
//	VECTOR _vPos;         // ���W
	float  _shotAngle;    // �e�𔭎˂���p�x
	bool   _shotFlag;     // ���˃t���O
	VECTOR _capslPos1, _capslPos2;
};