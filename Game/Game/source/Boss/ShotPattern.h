/**
 * @file   ShotPattern.h
 * @brief  弾幕パターン処理
 * 
 * @author matsuo tadahiko
 * @date   2021/03/22
 */

#pragma once

#include "Boss.h"

/**
 * 弾幕パターン処理
 */
class ShotPattern {
public:
	/**
     * @brief 弾幕パターン切替処理
     */
	void ShotPatternSwitch(Boss* boss);
	/**
     * @brief 弾幕パターン1&2
     */
	void ShotPattern1and2(Boss* boss);

	/**
	 * @brief 弾幕パターン3
	 */
	void ShotPattern3(Boss* boss);

	/**
	 * @brief 弾幕パターン4-1
	 */
	void ShotPattern4_1(Boss* boss);

	/**
	 * @brief 弾幕パターン4-2
	 */
	void ShotPattern4_2(Boss* boss);

	/**
	 * @brief 弾幕パターン5
	 */
	void ShotPattern5(Boss* boss);

	/**
	 * @brief 弾幕パターン6
	 */
	void ShotPattern6(Boss* boss);

	/**
	 * @brief 弾幕パターン7
	 */
	void ShotPattern7(Boss* boss);

	/**
	 * @brief レーザー攻撃1-1
	 */
	void LaserAttack1_1(Boss* boss);

	/**
	 * @brief レーザー攻撃1-2
	 */
	void LaserAttack1_2(Boss* boss);

	/**
	 * @brief レーザー攻撃2
	 */
	void LaserAttack2(Boss* boss);

private:
	static constexpr int PATTERN_CHANGE_CNT = 240; // 弾幕パターンを変化させるカウント最大値
	static constexpr int SHOT_REVERSE_CNT = 90;    // 弾幕回転方向を変化させるカウント最大値
	static constexpr float SHOT_DISTANCE = 10.0f;  // 弾幕を発生させる位置(ボス中心からの距離)
};
