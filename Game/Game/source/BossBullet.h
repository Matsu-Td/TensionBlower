/**
 * @file   BossBullet.h
 * @brief  ボスの弾幕処理
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#pragma once

#include "appframe.h"
#include "ObjectBase.h"

class BossBullet : public ObjectBase{
public:
	/**
	 * @brief  弾幕用弾生成
	 * @param  pos 弾生成位置
	 * @param  shotSpd 弾の移動処理
	 * @param  shotAngle 弾の移動角度
	 */
	BossBullet(VECTOR pos, float shotSpd, float shotAngle);
    ~BossBullet();

	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::BOSS_BULLET; }

	/**
	 * @brief 初期化
	 */
	void Initialize();

	/**
	 * @brief フレーム処理：計算
	 */
	void Process();

	/**
	 * @brief フレーム処理：描画
	 */
	void Render();

	/**
	 * @brief 弾の移動処理
	 */
	void MoveShot();

	/**
	 * @brief 弾き返し処理
	 */
	void Repel();

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

	/**
	 * @brief 当たり判定
	 */
	void Collision();

private:
	int   _cg[2];
	float _shotSpd;         // 弾の移動速度
	float _shotAngle;       // 弾幕発生角度
	bool  _camStateMLS;     // カメラ状態:マルチロックオンシステム発動中か
	bool  _canLockFlag;     // MLSでロック可能距離となる
	bool  _repelFlag;       // 弾かれたか(true:弾かれた, false:弾かれてない)
	float _bulletDir;       // -1.0fでMLSによる弾のはじき返し

	static constexpr float REPEL_SPD = 3.0f; // 弾き返された後の弾の移動速度
	static constexpr float MLS_SPD = 0.01f;  // マルチロックオンシステム中の速度計算(通常の1/100に)
};