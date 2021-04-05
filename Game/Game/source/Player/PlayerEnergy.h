/**
 * @file   PlayerEnergy.h
 * @brief  �v���C���[�G�l���M�[�֌W����
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#pragma once

#include "appframe.h"
#include "Player.h"

/**
 * @brief �v���C���[�G�l���M�[�֌W����
 */
class PlayerEnergy {
public:
	/**
     * @brief �G�l���M�[�����
	 * @param player �v���C���[�N���X�I�u�W�F�N�g�̃|�C���^
     * @param costEnergy �G�l���M�[�����
     */
	void CostEnergy(Player* player, int costEnergy);

	/**
     * @brief �G�l���M�[�Ǘ�
	 * @param player �v���C���[�N���X�I�u�W�F�N�g�̃|�C���^
     * @param oldState �����O�̃v���C���[�̏��
     */
	void EnergyManager(Player* player, Player::STATE oldState);
};
