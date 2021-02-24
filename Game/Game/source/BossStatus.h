#pragma once

/**
 * @file  BossStatus.h
 * @brief �{�X�X�e�[�^�XUI�`��
 *
 * @date 2021-02-25
 */

#include "appframe.h"

class BossStatus {
public:
	BossStatus();
	~BossStatus();

	void Render();

private:
	// �摜
	int _cgName;    // ���O
	int _cgFrame;   // �X�e�[�^�X�̃t���[��
	int _cgFrameBg; // �X�e�[�^�X�̃t���[���̔w��
	int _cgHP[5];   // HP�o�[
	int _cgShield;  // �V�[���h�o�[

	static constexpr int HP_BAR_NUM = 5;  // HP�o�[�{��
	const TCHAR* _cgString[HP_BAR_NUM] =  // HP�o�[�摜�t�@�C����
	{ "res/ui/boss/enemy_hp_1.png","res/ui/boss/enemy_hp_2.png",
	  "res/ui/boss/enemy_hp_3.png","res/ui/boss/enemy_hp_4.png",
	  "res/ui/boss/enemy_hp_5.png" };

	// �摜�`����W �萔��`
	static constexpr int FRAME_POS_X = 1090; // �X�e�[�^�X�o�[�̃t���[��X���W
	static constexpr int FRAME_POS_Y = 30;   // �X�e�[�^�X�o�[�̃t���[��Y���W

	static constexpr int NAME_POS_X = 1650;  // �{�X��X���W
	static constexpr int NAME_POS_Y = 130;   // �{�X��Y���W

	static constexpr int HP_ONE = 1000;      // HP�o�[1�{�������HP��
	static constexpr int HP_SIZE= 750;       // HP�o�[����
	static constexpr int HP_POS_X_L = 1113;  // HP�o�[����X���W
	static constexpr int HP_POS_Y_L = 45;    // HP�o�[����Y���W
	static constexpr int HP_POS_X_R = 1853;  // HP�o�[�E��X���W
	static constexpr int HP_POS_Y_R = 80;    // HP�o�[�E��Y���W

	static constexpr int SHIELD_ONE = 1000;     // �V�[���h�o�[1�{������̃V�[���h��
	static constexpr int SHIELD_SIZE = 738;     // �V�[���h�o�[����
	static constexpr int SHIELD_POS_X_L = 1124; // �V�[���h�o�[����X���W
	static constexpr int SHIELD_POS_Y_L = 90;   // �V�[���h�o�[����Y���W
	static constexpr int SHIELD_POS_X_R = 1862; // �V�[���h�o�[�E��X���W
	static constexpr int SHIELD_POS_Y_R = 120;  // �V�[���h�o�[�E��Y���W
};
