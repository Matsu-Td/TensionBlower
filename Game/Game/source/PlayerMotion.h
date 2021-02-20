#pragma once

/**
 * @file  PlayerMotion.h
 * @brief �v���C���[���[�V�����ؑ�
 *
 * @date 2021-02-13
 */

#include "Player.h"

class PlayerMotion {
public:
	PlayerMotion();

	/**
	 * �v���C���[���[�V�����ؑ�
	 * @param player �v���C���[�N���X�I�u�W�F�N�g�̃|�C���^
	 * @param oldState �v���C���[�̏����O�̏��
	 */
	void SwitchMotion(Player* player, Player::STATE oldState);
};