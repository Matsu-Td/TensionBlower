#pragma once
#include "appframe.h"

class PlayerBullet {
public:
	PlayerBullet();
	~PlayerBullet();

	void Initialize();
	void Process();
	void Render();

private:
	int    _mh;           // モデルハンドル
	VECTOR _vPos;         // 座標
	float  _shotAngle;    // 弾を発射する角度
	bool   _shotFlag;     // 発射フラグ

	static constexpr int MAX_BULLETS = 100; // 装弾数最大
};