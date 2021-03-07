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
     * @brief �ˌ��U�� :�Q�[���p�b�hRT�Ŏˌ�
	 * @param player �v���C���[�N���X�I�u�W�F�N�g�̃|�C���^
	 * @param inputRT �Q�[���p�b�h�uRT�v���͒l
     */
	void ShootingAttack(Player* player, float inputRT);
};