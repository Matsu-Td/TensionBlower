/**
 * @file   BossStatus.h
 * @brief  �{�X�X�e�[�^�XUI�`�揈��
 * 
 * @author matsuo tadahiko
 * @date   2021/02/25
 */

#pragma once

#include "appframe.h"

/**
 * @brief �{�X�X�e�[�^�XUI�`�揈��
 */
class BossStatus {
public:
	BossStatus();
	~BossStatus();

	/**
	 * @brief �t���[�������F�`��
	 */
	void Render();

private:
	// �摜
	int _cgName;    // ���O
	int _cgFrame;   // �X�e�[�^�X�̃t���[��
	int _cgFrameBg; // �X�e�[�^�X�̃t���[���̔w��
	
	int _cgShield;  // �V�[���h�o�[

	static const int HP_BAR_NUM = 5;  // HP�o�[�{��
	const TCHAR* _hpBarString[HP_BAR_NUM] =  // HP�o�[�摜�t�@�C����
	{ "res/ui/boss/enemy_hp_1.png","res/ui/boss/enemy_hp_2.png",
	  "res/ui/boss/enemy_hp_3.png","res/ui/boss/enemy_hp_4.png",
	  "res/ui/boss/enemy_hp_5.png" };

	const TCHAR* _iconString[HP_BAR_NUM] =  // HP�o�[�摜�t�@�C����
	{ "res/ui/boss/enemy_hpicon_1.png","res/ui/boss/enemy_hpicon_2.png",
	  "res/ui/boss/enemy_hpicon_3.png","res/ui/boss/enemy_hpicon_4.png",
	  "res/ui/boss/enemy_hpicon_5.png" };

	int _cgHP[HP_BAR_NUM];    // HP�o�[
	int _cgIcon[HP_BAR_NUM];  // HP�o�[�{���\���p

	const int ICON_POS_X[HP_BAR_NUM] =
	{ 1816,1784,1752,1720,1688 };
	const int ICON_POS_Y = 21;

	// �摜�`����W �萔��`
	const int FRAME_POS_X = 1090;  // �X�e�[�^�X�o�[�̃t���[��X���W
	const int FRAME_POS_Y = 10;    // �X�e�[�^�X�o�[�̃t���[��Y���W
	const int FRAME_BG_POS_Y = 30; // �X�e�[�^�X�o�[�̔w�iY���W

	const int NAME_POS_X = 1650;  // �{�X��X���W
	const int NAME_POS_Y = 130;   // �{�X��Y���W

	const int HP_ONE = 1000;      // HP�o�[1�{�������HP��
	const int HP_SIZE= 750;       // HP�o�[����
	const int HP_POS_X_L = 1113;  // HP�o�[����X���W
	const int HP_POS_Y_L = 45;    // HP�o�[����Y���W
	const int HP_POS_X_R = 1853;  // HP�o�[�E��X���W
	const int HP_POS_Y_R = 80;    // HP�o�[�E��Y���W

	const int SHIELD_ONE = 1000;     // �V�[���h�o�[1�{������̃V�[���h��
	const int SHIELD_SIZE = 738;     // �V�[���h�o�[����
	const int SHIELD_POS_X_L = 1124; // �V�[���h�o�[����X���W
	const int SHIELD_POS_Y_L = 90;   // �V�[���h�o�[����Y���W
	const int SHIELD_POS_X_R = 1862; // �V�[���h�o�[�E��X���W
	const int SHIELD_POS_Y_R = 120;  // �V�[���h�o�[�E��Y���W
};
