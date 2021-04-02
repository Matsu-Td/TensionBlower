/**
 * @file   BossDamage.h
 * @brief  �{�X���󂯂�_���[�W����
 * 
 * @author matsuo tadahiko
 * @date   2021/03/22
 */
#pragma once

#include "Boss.h"

/**
 * �{�X���󂯂�_���[�W����
 */
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
	static constexpr int EXPLOSION_DMG_NORM = 2;   // ����HP�_���[�W�ʁF�ʏ펞(�V�[���h��)
	static constexpr int EXPLOSION_DMG_HP = 1;     // ����HP�_���[�W��(�V�[���h�L)
	static constexpr int EXPLOSION_DMG_SLD = 2;    // �����V�[���h�_���[�W��(�V�[���h�L)
};
