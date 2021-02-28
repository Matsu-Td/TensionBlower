/**
 * @file   PlayerShoot.h
 * @brief  プレイヤー射撃攻撃
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#pragma once

#include "appframe.h"
#include "Player.h"

class PlayerShoot {
public:
	PlayerShoot();

	/**
     * 射撃攻撃 :ゲームパッドRTで射撃
	 * @param player プレイヤークラスオブジェクトのポインタ
     */
	void ShootingAttack(Player* player);
};