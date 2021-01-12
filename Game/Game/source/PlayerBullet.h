#pragma once
#include "appframe.h"
#include "BulletBase.h"

class PlayerBullet : public ObjectBase{
public:
	PlayerBullet();
	~PlayerBullet();

	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::PLAYER_BULLET; }

	void Initialize();
	void Process();
	void Render();

private:
	int    _mh;           // ���f���n���h��
	VECTOR _vPos;         // ���W
	float  _shotAngle;    // �e�𔭎˂���p�x
	bool   _shotFlag;     // ���˃t���O
	VECTOR _capslPos1, _capslPos2;
};