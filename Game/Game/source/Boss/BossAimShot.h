/**
 * @file   BossAimShot.h
 * @brief  ボスの狙い撃ち弾処理
 * 
 * @author matsuo tadahiko
 * @date   2021/03/15
 */

#pragma once

#include "ShotBase.h"

/**
 * @brief ボスの狙い撃ち弾処理
 */
class BossAimShot :public ShotBase {
public:
	/**
	 * @brief  狙い撃ち弾の生成
	 * @param  pos 生成位置
	 * @param  shotSpd 弾の移動速度
	 * @param  shotAngle 弾の移動角度、方向　
	 */
	BossAimShot(VECTOR pos, float shotSpd, float shotAngle);
	~BossAimShot();

	OBJECTTYPE GetType()  override { return ObjectBase::OBJECTTYPE::BOSS_BULLET; }

	/**
	 * @brief フレーム処理：計算
	 */
	void Process() override;
};
