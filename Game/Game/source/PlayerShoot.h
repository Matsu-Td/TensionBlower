#pragma once

/**
 * @file  PlayerShoot.h
 * @brief �v���C���[�ˌ��U��
 *
 * @date 2021-02-14
 */

#include "appframe.h"
#include "Player.h"

class PlayerShoot {
public:
	PlayerShoot();

	/**
     * �ˌ��U�� :�Q�[���p�b�hRT�Ŏˌ�
     */
	void ShootingAttack(Player* player);
};