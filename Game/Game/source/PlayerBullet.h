#pragma once
#include "appframe.h"
#include <string>
#include <vector>

class PlayerBullet : public ObjectBase {
public:
	PlayerBullet();
	~PlayerBullet();

	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::PLAYER_BULLET; }

	void Initialize();
	void Process();
	void Render();

	void SetShotAngle(float shotAngle) { _shotAngle = shotAngle; }

	int		_effectResourceHandle;		// エフェクトファイルをロードするハンドル
	int		_playingEffectHandle;		// ロードしたエフェクトファイルから、エフェクトを生成したもの
private:
	float  _shotAngle;    // 弾を発射する角度
	bool   _shotFlag;     // 発射フラグ

	static constexpr float ADJ_DEG = 90.0f;  // 角度(弾の向き)ずれ分調整
};