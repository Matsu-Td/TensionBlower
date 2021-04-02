/**
 * @file   Explosion.h
 * @brief  �{���U���̔����G�t�F�N�g
 * 
 * @author matsuo tadahiko
 * @date   2021/03/05
 */

#pragma once
#include "appframe.h"
#include "../Object/ObjectBase.h"
#include "../Boss/BossDamage.h"

class Explosion : public ObjectBase{
public:
	/**
	 * �{���U���̔����G�t�F�N�g����
	 * @param pos ���������ʒu
	 * @param repelFlag �e���Ԃ��ꂽ�e���ǂ���
	 */
	Explosion(VECTOR pos, bool repelFlag);
	~Explosion();

	OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::EXPLOSION; }

	/**
	 * ������
	 */
	void Initialize() override;

	/**
	 * �t���[�������F�v�Z
	 */
	void Process() override;

	/**
	 * �t���[�������F�`��
	 */
	void Render() override;

	/**
	 * �{�X�Ƃ̓����蔻��
	 */
	void CollisionToBoss();

	/**
	 * �v���C���[�Ƃ̓����蔻��
	 */
	void CollisionToPlayer();

private:
	int _effectCnt;     // �G�t�F�N�g�J�E���g
	int _repelFlag;     // �e���Ԃ��ꂽ�e���ǂ���(true:�e���Ԃ��ꂽ�e)
	int	_effectHandle;  // �G�t�F�N�g�t�@�C�������[�h����n���h��
	int	_playingHandle;	// ���[�h�����G�t�F�N�g�t�@�C������A�G�t�F�N�g�𐶐���������

	const int ALL_EFFECT_TIME = 180;   // �G�t�F�N�g���Đ�����
	const float MAX_RADIUS    = 10.0f; // �ő唼�a�T�C�Y

	std::unique_ptr<BossDamage> _bossDamageCall;  	// �{�X�ւ̃_���[�W�����Ăяo��
};
