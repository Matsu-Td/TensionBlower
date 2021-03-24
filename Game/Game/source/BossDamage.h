/**
 * @file   BossDamage.h
 * @brief  �{�X�ւ̃_���[�W����
 * 
 * @author matsuo tadahiko
 * @date   2021/03/22
 */
#pragma once

#include "Boss.h"

class BossDamage {
public:
	/**
     * �v���C���[�ɒe���Ԃ��ꂽ�e�ɂ��_���[�W����
     */
	void RepelDamage(Boss* boss);

	/**
	 * �v���C���[����󂯂��_���[�W�ʌv�Z
	 */
	void AttackDamage(Boss* boss);

	/**
	 * �q�b�g�|�C���g�ւ̔����_���[�W
	 */
	void ExplosionDamageHP(Boss* boss);

	/**
	 * �V�[���h�ւ̔����_���[�W
	 */
	void ExplosionDamageShield(Boss* boss);
private:
	const int EXPLOSION_DMG_NORM = 2;   // ����HP�_���[�W�ʁF�ʏ펞(�V�[���h��)
	const int EXPLOSION_DMG_HP = 1;     // ����HP�_���[�W��(�V�[���h�L)
	const int EXPLOSION_DMG_SLD = 2;    // �����V�[���h�_���[�W��(�V�[���h�L)
};