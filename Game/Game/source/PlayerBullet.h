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
	float  _shotAngle;    // ’e‚ð”­ŽË‚·‚éŠp“x
	bool   _shotFlag;     // ”­ŽËƒtƒ‰ƒO
};