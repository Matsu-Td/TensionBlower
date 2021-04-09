/**
 * @file   BossBullet.h
 * @brief  ボスの弾幕処理
 * 
 * @author matsuo tadahiko
 * @date   2020/12/22
 */

#pragma once

#include "ShotBase.h"

/**
 * @brief ボスの弾幕処理
 */
class BossBullet : public ShotBase {
public:
	/**
	 * @brief 弾幕用弾生成
	 * @param pos 弾生成位置
	 * @param shotSpd 弾の移動速度
	 * @param shotAngle 弾の移動角度
	 */
	BossBullet(VECTOR pos, float shotSpd, float shotAngle);
    ~BossBullet();

	OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::BOSS_BULLET; }

	/**
	 * @brief フレーム処理：計算
	 */
	void Process() override;

	/**
	 * @brief 弾き返し処理
	 */
	void Repel();

	/**
	 * @brief 当たり判定
	 */
	void Collision() override;
};