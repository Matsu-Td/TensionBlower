/**
 * @file   PlayerShoot.h
 * @brief  �v���C���[�ˌ��U��
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
     * �ˌ��U�� :�Q�[���p�b�hRT�Ŏˌ�
	 * @param player �v���C���[�N���X�I�u�W�F�N�g�̃|�C���^
     */
	void ShootingAttack(Player* player);
};