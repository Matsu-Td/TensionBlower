/**
 * @file   BossHit.h
 * @brief  ボスへのヒットエフェクト
 *
 * @author matsuo tadahiko
 * @date   2021/03/15
 */
#pragma once

#include "appframe.h"
#include "ObjectBase.h"

class BossHit : public ObjectBase {
public:
	/**
	 * @brief ボスへのヒットエフェクト生成
	 * @param 生成位置
	 */
	BossHit(VECTOR pos);
	~BossHit();

	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::BOSS_HIT; }

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

private:
	int _effectCnt;     // エフェクトカウント
	int	_effectHandle;  // エフェクトファイルをロードするハンドル
	int	_playingHandle;	// ロードしたエフェクトファイルから、エフェクトを生成したもの

	static constexpr int ALL_EFFECT_TIME = 30;  // エフェクト総再生時間
};
