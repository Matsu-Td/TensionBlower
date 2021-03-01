/**
 * @file   PlayerJump.h
 * @brief  �v���C���[�W�����v����
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#pragma once

#include "appframe.h"
#include "Player.h"

class PlayerJump {
public:
	/**
	 * @brief �W�����v����
	 * @param player �v���C���[�N���X�I�u�W�F�N�g�̃|�C���^
	 */
	void JumpAction(Player* player);

private:
	static constexpr float IN_VEL = 4.0f;      // ����
	static constexpr float MULT_HALF = 0.5f;   // 1/2��Z
	static constexpr float JUMP_CNT = 0.2f;    // �W�����v����
};
