/**
 * @file   Explosion.h
 * @brief  �{���U���̔����G�t�F�N�g
 * 
 * @author matsuo tadahiko
 * @date   2021/03/05
 */

#pragma once
#include "appframe.h"
#include "ObjectBase.h"

class Explosion : public ObjectBase{
public:
	/**
	 * @brief �{���U���̔����G�t�F�N�g����
	 * @param pos ���������ʒu
	 * @param repelFlag �e���Ԃ��ꂽ�e���ǂ���
	 */
	Explosion(VECTOR pos, bool repelFlag);
	~Explosion();

	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::EXPLOSION; }

	/**
	 * @brief ������
	 */
	void Initialize();

	/**
	 * @brief �t���[�������F�v�Z
	 */
	void Process();

	/**
	 * @brief �t���[�������F�`��
	 */
	void Render();

	/**
	 * @brief �{�X�Ƃ̓����蔻��
	 */
	void CollisionToBoss();

	/**
	 * @brief �v���C���[�Ƃ̓����蔻��
	 */
	void CollisionToPlayer();

private:
	int _effectCnt;     // �G�t�F�N�g�J�E���g
	int _repelFlag;     // �e���Ԃ��ꂽ�e���ǂ���(true:�e���Ԃ��ꂽ�e)
	int	_effectHandle;  // �G�t�F�N�g�t�@�C�������[�h����n���h��
	int	_playingHandle;	// ���[�h�����G�t�F�N�g�t�@�C������A�G�t�F�N�g�𐶐���������

	static constexpr int ALL_EFFECT_TIME = 180;   // �G�t�F�N�g���Đ�����
	static constexpr float MAX_RADIUS    = 10.0f; // �ő唼�a�T�C�Y
};
