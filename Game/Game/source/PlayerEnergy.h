#pragma once

/**
 * @file  PlayerEnergy.h
 * @brief �v���C���[�G�l���M�[�֌W����
 *
 * @date 2021-02-14
 */

#include "appframe.h"
#include "Player.h"

class PlayerEnergy {
public:
	PlayerEnergy();
	~PlayerEnergy();

	/**
     * �G�l���M�[�����
     * @param costEnergy �G�l���M�[�����
     */
	void CostEnergy(Player* player, float costEnergy);

	/**
     * �G�l���M�[�Ǘ�
     * @param oldState �����O�̃v���C���[�̏��
     */
	void EnergyManager(Player* player, Player::STATE oldState);
};
