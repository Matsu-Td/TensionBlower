/**
 * @file   Explosion.h
 * @brief  ボム攻撃の爆発エフェクト
 * 
 * @author matsuo tadahiko
 * @date   2021/03/05
 */

#pragma once
#include "appframe.h"
#include "ObjectBase.h"

class Explosion : public ObjectBase{
public:
	/**
	 * @brief ボム攻撃の爆発エフェクト生成
	 * @param pos 爆発発生位置
	 * @param repelFlag 弾き返された弾かどうか
	 */
	Explosion(VECTOR pos, bool repelFlag);
	~Explosion();

	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::EXPLOSION; }

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
	 * @brief ボスとの当たり判定
	 */
	void CollisionToBoss();

	/**
	 * @brief プレイヤーとの当たり判定
	 */
	void CollisionToPlayer();

private:
	int _effectCnt;     // エフェクトカウント
	int _repelFlag;     // 弾き返された弾かどうか(true:弾き返された弾)
	int	_effectHandle;  // エフェクトファイルをロードするハンドル
	int	_playingHandle;	// ロードしたエフェクトファイルから、エフェクトを生成したもの

	static constexpr int ALL_EFFECT_TIME = 180;   // エフェクト総再生時間
	static constexpr float MAX_RADIUS    = 10.0f; // 最大半径サイズ
};
