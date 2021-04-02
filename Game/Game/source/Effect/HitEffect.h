/**
 * @file   HitEffect.h
 * @brief  �ߐڍU���̃q�b�g�G�t�F�N�g
 *
 * @author matsuo tadahiko
 * @date   2021/03/15
 */
#pragma once

#include "appframe.h"
#include "../Object/ObjectBase.h"

class HitEffect : public ObjectBase {
public:
	/**
	 * �{�X�ւ̃q�b�g�G�t�F�N�g����
	 * @param �����ʒu
	 */
	HitEffect(VECTOR pos);
	~HitEffect();

	OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::HIT_EFFECT; }

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

private:
	int _effectCnt;     // �G�t�F�N�g�J�E���g
	int	_effectHandle;  // �G�t�F�N�g�t�@�C�������[�h����n���h��
	int	_playingHandle;	// ���[�h�����G�t�F�N�g�t�@�C������A�G�t�F�N�g�𐶐���������

	const int ALL_EFFECT_TIME = 30;  // �G�t�F�N�g���Đ�����
};
