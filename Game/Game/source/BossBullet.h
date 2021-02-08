#pragma once

/**
 * @file  BossBullet.h
 * @brief ボスの弾幕処理
 *
 * @date 2021-02-08
 */

#include "appframe.h"

class BossBullet : public ObjectBase{
public:
	BossBullet();
	virtual ~BossBullet();

	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::BOSS_BULLET; }

	void Initialize();
	void Process();
	void Render();
	void Shot();

	void SetAngle(float shotAngle) { _shotAngle = shotAngle; }
	void SetShotSpd(float shotSpd) { _shotSpd = shotSpd; }

private:
	int _cg[2];
	float _shotSpd;         // 弾の移動速度
	int _shotCnt;           // 
	int _mlsCnt;
	int _pattern;           // 弾幕パターン切替(3パターン)
	float _shotAngle;       // 弾幕発生角度
	float _setAngle;        // 弾幕発生角度設定
	float shotInterval;     // 弾幕発生インターバル
	bool _camStateMLS;      // カメラ状態:マルチロックオンシステム発動中か
	bool _canLockFlag;      // MLSでロック可能距離となる
	bool _repelFlag;        // 弾かれたか(true:弾かれた, false:弾かれてない)
	float _bulletDir;       // -1.0fでMLSによる弾のはじき返し

	static constexpr float NOR_SPD = 1.0f;
};