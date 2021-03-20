/**
 * @file   BossHit.h
 * @brief  �{�X�ւ̃q�b�g�G�t�F�N�g
 *
 * @author matsuo tadahiko
 * @date   2021/03/15
 */
#pragma once

#include "appframe.h"
#include "ObjectBase.h"

class BossHit : public ObjectBase {
public:
	/**
	 * @brief �{�X�ւ̃q�b�g�G�t�F�N�g����
	 * @param �����ʒu
	 */
	BossHit(VECTOR pos);
	~BossHit();

	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::BOSS_HIT; }

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

private:
	int _effectCnt;     // �G�t�F�N�g�J�E���g
	int	_effectHandle;  // �G�t�F�N�g�t�@�C�������[�h����n���h��
	int	_playingHandle;	// ���[�h�����G�t�F�N�g�t�@�C������A�G�t�F�N�g�𐶐���������

	static constexpr int ALL_EFFECT_TIME = 30;  // �G�t�F�N�g���Đ�����
};
