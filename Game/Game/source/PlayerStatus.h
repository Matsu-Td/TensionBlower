/**
 * @file   PlayerStatus.h
 * @brief  �v���C���[�X�e�[�^�XUI�`��
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#pragma once

#include "appframe.h"

class PlayerStatus {
public:
	PlayerStatus();
	~PlayerStatus();

	/**
	 * @brief �t���[�������F�`��
	 */
	void Render();

private:
	// �摜
	int _cgName;       // ���O    
	int _cgFrame;      // �X�e�[�^�X�̃t���[��
	int _cgFrameBg;    // �X�e�[�^�X�̃t���[���̔w�i
	int _cgBarHP;      // HP�o�[
	int _cgBarEnergy;  // �G�l���M�[�o�[


	// �摜�`����W�@�萔��`
	static constexpr int STATUS_FRAME_POS = 30; // �X�e�[�^�X�o�[���W
	static constexpr int HP_BAR_SIZE = 740;     // HP�o�[�����T�C�Y
	static constexpr int ENERGY_BAR_SIZE = 738; // �G�l���M�[�o�[�����T�C�Y

	static constexpr int HP_POS_X_L = 68;       // HP�o�[����X���W
	static constexpr int HP_POS_Y_L = 45;       // HP�o�[����Y���W
	static constexpr int HP_POS_Y_R = 80;       // HP�o�[�E��Y���W

	static constexpr int ENERGY_POS_X_L = 59;   // �G�l���M�[�o�[����X���W
	static constexpr int ENERGY_POS_Y_L = 90;   // �G�l���M�[�o�[����Y���W
	static constexpr int ENERGY_POS_Y_R = 120;  // �G�l���M�[�o�[�E��Y���W

	static constexpr int NUM_FRAME_POS_X = 30;  // ���e���t���[��X���W
	static constexpr int NUM_FRAME_POS_Y = 900; // ���e���t���[��Y���W

	static constexpr int NAME_POS_X = 0;   // �v���C���[��X���W
	static constexpr int NAME_POS_Y = 130; // �v���C���[��Y���W
};