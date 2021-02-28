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

class PlayerEnergy {
public:
	PlayerEnergy();
	~PlayerEnergy();

	/**
     * �G�l���M�[�����
	 * @param player �v���C���[�N���X�I�u�W�F�N�g�̃|�C���^
     * @param costEnergy �G�l���M�[�����
     */
	void CostEnergy(Player* player, float costEnergy);

	/**
     * �G�l���M�[�Ǘ�
	 * @param player �v���C���[�N���X�I�u�W�F�N�g�̃|�C���^
     * @param oldState �����O�̃v���C���[�̏��
     */
	void EnergyManager(Player* player, Player::STATE oldState);
};
