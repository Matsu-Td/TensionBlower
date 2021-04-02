/**
 * @file   BossDamage.cpp
 * @brief�@�{�X���󂯂�_���[�W����
 * 
 * @author matsuo tadahiko
 * @date   2021/03/22
 */

#include "BossDamage.h"
#include "../Mode/ModeGame.h"
#include "../Sound/Sound.h"

 /**
  * �v���C���[�ɒe���Ԃ��ꂽ�e�ɂ��_���[�W����
  */
void BossDamage::RepelDamage(Boss* boss) {

	ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
	PlaySoundMem(gSound._se["hit"], DX_PLAYTYPE_BACK);
	// �V�[���h������Ƃ�
	if (boss->_shield > 0) {
		boss->_hitpoint -= modeGame->_charaData->_repelDmgHP;
		boss->_shield -= modeGame->_charaData->_repelDmgSld;

		if (boss->_shield <= 0) {
			boss->_shield = 0;
			boss->_mlsDownFlag = true;  // �v���C���[�ɒe���Ԃ��ꂽ�e�ŃV�[���h���j�󂳂���true
		}
	}
	// �V�[���h���Ȃ��Ƃ�
	else {
		boss->_hitpoint -= modeGame->_charaData->_repelDmg;
	}
}

/**
 * �v���C���[����󂯂��_���[�W�ʌv�Z
 */
void BossDamage::AttackDamage(Boss* boss) {

	// �_�E����Ԏ��̂ݔ�e���̐��f�[�^�Đ�
	if (boss->_state == Boss::STATE::DOWN) {
		boss->PlayVoice("hidan");
	}
	// �q�b�g���Đ�
	PlaySoundMem(gSound._se["hit_boss"], DX_PLAYTYPE_BACK);

	// �_���[�W�ʊi�[
	int dmgHP = Player::GetInstance()->GetNowDmgHP();
	int dmgSld = Player::GetInstance()->GetNowDmgSld();
	int dmgNorm = Player::GetInstance()->GetNowDmgNorm();
	// �V�[���h������Ƃ�
	if (boss->_shield > 0) {
		boss->_hitpoint -= dmgHP;
		boss->_shield -= dmgSld;
		if (boss->_shield <= 0) {
			boss->_shield = 0;
		}
	}
	// �V�[���h���Ȃ��Ƃ�
	else {
		boss->_hitpoint -= dmgNorm;
	}
}

/**
 * �q�b�g�|�C���g�ւ̔����_���[�W
 */
void BossDamage::ExplosionDamageHP(Boss* boss) {
	// �V�[���h������Ƃ�
	if (boss->_shield > 0) {
		boss->_hitpoint -= EXPLOSION_DMG_HP;
	}
	// �V�[���h���Ȃ��Ƃ�
	else {
		boss->_hitpoint -= EXPLOSION_DMG_NORM;
	}
}

/**
 * �V�[���h�ւ̔����_���[�W
 */
void BossDamage::ExplosionDamageShield(Boss* boss) {
	// �V�[���h������Ƃ�
	if (boss->_shield > 0) {
		boss->_shield -= EXPLOSION_DMG_SLD;
		if (boss->_shield <= 0) {
			boss->_shield = 0;
		}
	}
}
