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
	int    _mh;           // モデルハンドル
	VECTOR _vPos;         // 座標
	float  _shotAngle;    // 弾を発射する角度
	bool   _shotFlag;     // 発射フラグ
	VECTOR _capslPos1, _capslPos2;
};