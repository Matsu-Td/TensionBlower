/**
 * @file   PlayerBullet.h
 * @brief  プレイヤー射撃用の弾移動処理
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#pragma once

#include "appframe.h"
#include <string>
#include <vector>

class PlayerBullet : public ObjectBase {
public:
	PlayerBullet();
	~PlayerBullet();

	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::PLAYER_BULLET; }
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

	void SetShotAngle(float shotAngle) { _shotAngle = shotAngle; }

	int		_effectResourceHandle;		// エフェクトファイルをロードするハンドル
	int		_playingEffectHandle;		// ロードしたエフェクトファイルから、エフェクトを生成したもの
private:
	float  _shotAngle;    // 弾を発射する角度
	bool   _shotFlag;     // 発射フラグ

	static constexpr float ADJ_DEG = 90.0f;  // 角度(弾の向き)ずれ分調整
};