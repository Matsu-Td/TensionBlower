/** 
 * @file   BossDamage.cpp
 * @brief  �{�X���󂯂�_���[�W����
 * 
 * @author matsuo tadahiko
 * @date   2021/04/06
 */

#include "Boss.h"
#include "../Mode/ModeGame.h"
#include "../Sound/Sound.h"

using namespace tensionblower;

  /*
   * �v���C���[�ɒe���Ԃ��ꂽ�e�ɂ��_���[�W����
   */
void Boss::RepelDamage() {

	mode::ModeGame* modeGame = static_cast<mode::ModeGame*>(ModeServer::GetInstance()->Get("game"));

	PlaySoundMem(gSound._se["hit"], DX_PLAYTYPE_BACK);
	// �V�[���h������Ƃ�
	if (_shield > 0) {
		_hitpoint -= modeGame->_charaData->_repelDmgHP;
		_shield -= modeGame->_charaData->_repelDmgSld;

		if (_shield <= 0) {
			_shield = 0;
			_mlsDownFlag = true;  // �v���C���[�ɒe���Ԃ��ꂽ�e�ŃV�[���h���j�󂳂���true
		}
	}
	// �V�[���h���Ȃ��Ƃ�
	else {
		_hitpoint -= modeGame->_charaData->_repelDmg;
	}
}

/*
 * �v���C���[����󂯂��_���[�W�ʌv�Z
 */
void Boss::AttackDamage() {

	// �_�E����Ԏ��̂ݔ�e���̐��f�[�^�Đ�
	if (_state == Boss::STATE::DOWN) {
		PlayVoice("hidan");
	}
	// �q�b�g���Đ�
	PlaySoundMem(gSound._se["hit_boss"], DX_PLAYTYPE_BACK);

	// �_���[�W�ʊi�[
	int dmgHP = Player::GetInstance()->GetNowDmgHP();
	int dmgSld = Player::GetInstance()->GetNowDmgSld();
	int dmgNorm = Player::GetInstance()->GetNowDmgNorm();

	// �V�[���h������Ƃ�
	if (_shield > 0) {
		_hitpoint -= dmgHP;
		_shield -= dmgSld;
		if (_shield <= 0) {
			_shield = 0;
		}
	}
	// �V�[���h���Ȃ��Ƃ�
	else {
		_hitpoint -= dmgNorm;
	}
}

/*
 * �q�b�g�|�C���g�ւ̔����_���[�W
 */
void Boss::ExplosionDamageHP() {
	// �V�[���h������Ƃ�
	if (_shield > 0) {
		_hitpoint -= EXPLOSION_DMG_HP;
	}
	// �V�[���h���Ȃ��Ƃ�
	else {
		_hitpoint -= EXPLOSION_DMG_NORM;
	}
}

/*
 * �V�[���h�ւ̔����_���[�W
 */
void Boss::ExplosionDamageShield() {
	// �V�[���h������Ƃ�
	if (_shield > 0) {
		_shield -= EXPLOSION_DMG_SLD;
		if (_shield <= 0) {
			_shield = 0;
		}
	}
}
