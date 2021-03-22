/**
 * @file   HitEffect.h
 * @brief  �ߐڍU���̃q�b�g�G�t�F�N�g
 *
 * @author matsuo tadahiko
 * @date   2021/03/15
 */
#pragma once

#include "appframe.h"
#include "ObjectBase.h"

class HitEffect : public ObjectBase {
public:
	/**
	 * @brief �{�X�ւ̃q�b�g�G�t�F�N�g����
	 * @param �����ʒu
	 */
	HitEffect(VECTOR pos);
	~HitEffect();

	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::HIT_EFFECT; }

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
