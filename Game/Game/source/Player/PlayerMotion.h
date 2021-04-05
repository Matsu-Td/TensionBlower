/**
 * @file   PlayerMotion.h
 * @brief  �v���C���[���[�V�����ؑ֏���
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#pragma once

#include "Player.h"

/**
 * @brief �v���C���[���[�V�����ؑ֏���
 */
class PlayerMotion {
public:
	/**
	 * @brief �v���C���[���[�V�����ؑ�
	 * @param player �v���C���[�N���X�I�u�W�F�N�g�̃|�C���^
	 * @param oldState �v���C���[�̏����O�̏��
	 */
	void SwitchMotion(Player* player, Player::STATE oldState);
};