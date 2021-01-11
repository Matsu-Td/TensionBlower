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
//	int    _mh;           // モデルハンドル
//	VECTOR _vPos;         // 座標
	float  _shotAngle;    // 弾を発射する角度
	bool   _shotFlag;     // 発射フラグ
	VECTOR _capslPos1, _capslPos2;
};