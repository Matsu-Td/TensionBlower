/**
 * @file   PlayerShoot.h
 * @brief  vC[ËU
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
     * @brief ËU :Q[pbhRTÅË
	 * @param player vC[NXIuWFNgÌ|C^
     */
	void ShootingAttack(Player* player);
};