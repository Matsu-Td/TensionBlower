#pragma once

/**
 * @file  PlayerShoot.h
 * @brief プレイヤー射撃攻撃
 *
 * @date 2021-02-14
 */

#include "appframe.h"
#include "Player.h"

class PlayerShoot {
public:
	PlayerShoot();

	/**
     * 射撃攻撃 :ゲームパッドRTで射撃
     */
	void ShootingAttack(Player* player);
};