/**
 * @file   BossBullet.h
 * @brief  ボスの弾幕処理
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#pragma once

#include "appframe.h"

class BossBullet : public ObjectBase{
public:
	BossBullet();
    ~BossBullet();

	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::BOSS_BULLET; }

	void Initialize();
	void Process();
	void Render();

	/**
	 * 弾の移動処理
	 */
	void Shot();

	/**
	 * @brief 弾の角度を設定
	 * @param shotAngle 弾の角度
	 */
	void SetAngle(float shotAngle) { _shotAngle = shotAngle; }

	/**
	 * @brief 弾の速度を設定
	 * @param shotSpd 弾の速度
	 */
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
	static constexpr float MLS_SPD = 0.01f; // マルチロックオンシステム中の速度計算(通常の1/100に)
};