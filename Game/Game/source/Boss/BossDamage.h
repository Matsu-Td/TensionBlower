/**
 * @file   BossDamage.h
 * @brief  ボスが受けるダメージ処理
 * 
 * @author matsuo tadahiko
 * @date   2021/03/22
 */
#pragma once

#include "Boss.h"

/**
 * ボスが受けるダメージ処理
 */
class BossDamage {
public:
	/**
     * プレイヤーに弾き返された弾によるダメージ処理
     */
	void RepelDamage(Boss* boss);

	/**
	 * プレイヤーから受けたダメージ量計算
	 */
	void AttackDamage(Boss* boss);

	/**
	 * ヒットポイントへの爆発ダメージ
	 */
	void ExplosionDamageHP(Boss* boss);

	/**
	 * シールドへの爆発ダメージ
	 */
	void ExplosionDamageShield(Boss* boss);
private:
	static constexpr int EXPLOSION_DMG_NORM = 2;   // 爆発HPダメージ量：通常時(シールド無)
	static constexpr int EXPLOSION_DMG_HP = 1;     // 爆発HPダメージ量(シールド有)
	static constexpr int EXPLOSION_DMG_SLD = 2;    // 爆発シールドダメージ量(シールド有)
};
